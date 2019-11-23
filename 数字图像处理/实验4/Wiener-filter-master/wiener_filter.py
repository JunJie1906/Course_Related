import numpy as np
import numpy.fft as npf

def denoise(noisy_img, lbd, sigma):
    '''
    Wiener Filter for denoise
    
    Parameters
    ----------
    x : array-like
        The 2d spectrum of an image, complex, of shapes (M, N), (M, N, 3) or (M, N, 4)
    noise_img : numpy
        noisy image that you want to denoise
    lbd : 2d numpy
        kernel in frequency domain
    sigma : int
        standard deviation for denoise
    
    Returns
    -------
    xhat : Denoising image (value from 0 to 1)
    '''
    y = noisy_img.copy()
    z = npf.fftn(y)
    zhat = lbd**2/(lbd**2+sigma**2) * z
    xhat = np.real(npf.ifftn(zhat))
    xhat[xhat>1] = 1
    xhat[xhat<0] = 0
    return xhat


def fftgrid(n1, n2):
    '''
    Omega in frequency domain
    
    Parameters
    ----------
    n1 : int
        image width
    n2 : int
        image length
    
    Returns
    -------
    u, v : numpy.meshgrid
        omega meshgrid
    '''
    f1 = npf.fftfreq(n1, d=1./n1)
    f2 = npf.fftfreq(n2, d=1./n2)
    u, v = np.meshgrid(f1, f2, indexing='ij')
    return u, v

def average_power_spectral_density(x):
    '''
    Average power spectral density of some images
    
    Parameters
    ----------
    x : list
        A list of images 
    
    Returns
    -------
    S : numpy array
        average power spectral density of images
    '''
    K = len(x)
    tmp = np.zeros(x[0].shape[:2])
    
    for i in range(K):
        tmp += np.absolute(npf.fft2(x[i].mean(axis = 2)))**2
    
    S = (tmp / K)
    
    return S

def mean_power_spectrum_density(apsd):
    '''
    Mean power spectral density
    
    Parameters
    ----------
    apsd : numpy array
        average power spectral density of images 
    
    Returns
    -------
    mpsd : numpy array
        mean power spectral density
    alpha : float
        optimal parameter to minimize SSE
    beta : float
        optimal parameter to minimize SSE
    '''
    
    n1, n2 = apsd.shape
    n = n1*n2-1
    
    vv, uu = fftgrid(n1, n2)

    omega = np.sqrt((vv/n1)**2+(uu/n2)**2)
    omega = omega.flatten()[1:]

    s = (np.log(apsd) - np.log(n1) - np.log(n2)).flatten()[1:]
    t = np.log(omega)

    sum_t = t.sum()
    sum_s = s.sum()
    tmp = (t*s).sum()
    
    alpha = (n*tmp-sum_t*sum_s)/(n*((t**2).sum())-(sum_t)**2)

    beta = (sum_s-alpha*sum_t)/n
    
    mpsd = np.zeros(n1*n2)

    mpsd[1:] = n * np.exp(beta) * np.power(omega, alpha)

    mpsd[0] = np.inf
    mpsd = mpsd.reshape((n1, n2))
    return mpsd, alpha, beta

def deconvolve_wiener(x, lbd, sig, mpsd, return_transfer=False):
    '''
    Wiener Deconvolution for deblurring
    
    Parameters
    ----------
    x : numpy array
        blurring image
    lbd : numpy array
        kernel in frequency domain
    sig : float
        standard deviation sigma
    mpsd : numpy array
        mean power spectral density
    return_transfer : bool
        return transfer function or not
    
    Returns
    -------
    xdec : numpy array
        Deblurring image
    hhat : numpy array
        wiener deconvolution transfer function
    '''
    n1, n2 = x.shape[:2]
    hhat = np.conjugate(lbd)/(np.absolute(lbd)**2+n1*n2*(sig**2)/mpsd)
    x_fft = np.fft.fftn(x)
    xdec = np.real(np.fft.ifftn(hhat[:,:,None]*x_fft))
    if return_transfer:
        return xdec, hhat
    else:
        return xdec
    


