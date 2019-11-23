import numpy as np
import matplotlib.pyplot as plt
import numpy.fft as npf
import cv2
from wiener_filter import denoise, deconvolve_wiener


def shift(x, k, l, boundary):
    '''
    Shifting an image x of size (n1, n2) in a direction (k,l) consists of 
    creating a new image xshifted of size (n1, n2)
    
    Parameters
    ----------
    x : numpy array
        original image
    k : int
        direction for width
    l : int
        direction for length
    boundary : str
        mode for different kinds of shifting
        
    Returns
    -------
    xshifted : numpy array
        image after shifting
    '''
    if x.ndim == 2:
        color = 1
    else :
        color = 3
    n1 = np.shape(x)[0]
    n2 = np.shape(x)[1]
    xshifted = np.zeros((n1,n2,color))
    irange = np.mod(np.arange(n1) + k, n1)
    jrange = np.mod(np.arange(n2) + l, n2)
    # firstly move upward then move rightward
    xshifted = x[irange, :][:, jrange]
    if boundary == 'periodical':
        pass
    elif boundary is 'extension':
        m = n1 - k if k > 0 else -k-1
        n = n2 - l if l > 0 else -l-1
        if k != 0:
            xshifted[m::np.sign(k),:,:] = np.tile(xshifted[m-np.sign(k):m-np.sign(k)+1,:,:],(np.sign(k)*k,1,1))
        if l != 0:
            xshifted[:,n::np.sign(l),:] = np.tile(xshifted[:,n-np.sign(l):n-np.sign(l)+1,:],(1,np.sign(l)*l,1))
    elif boundary == 'zero-padding':
        xshifted = np.zeros(x.shape)

        i_seq = np.arange(max(-k, 0), min(n1-k, n1))
        j_seq = np.arange(max(-l, 0), min(n2-l, n2))
        xshifted[np.min(i_seq):np.max(i_seq)+1, np.min(j_seq):np.max(j_seq)+1,:] = x[i_seq + k,:][:, j_seq + l]
    # mirror
    else:
        m = n1 - k if k > 0 else -k
        n = n2 - l if l > 0 else -l
        add_k = 1 if k < 0 else 0
        add_l = 1 if l < 0 else 0
        if k != 0:
            xshifted[m::np.sign(k),:] = xshifted[min(m,m-k):max(m,m-k) + add_k,:][::-np.sign(k),:]
        if l != 0:
            xshifted[:,n::np.sign(l)] = xshifted[:,min(n,n-l):max(n,n-l) + add_l][:,::-np.sign(l)]
    return xshifted

def kernel(name, tau=1, eps = 1e-3):
    '''
    kernel function (gaussian, exponential or box)
    
    Parameters
    ----------
    name : str
        option for different kinds of kernel
    tau : int
        kernel parameter
    eps : float
        kernel parameter
        
    Returns
    -------
    nu : numpy array
        kernel
    '''
    
    if name.startswith('gaussian'):
        s1 = 0
        while True:
            if np.exp(-(s1**2)/(2*tau)) < eps:
                break
            s1 += 1
        s1 = s1-1
        s2 = s1
        if name.endswith('1'):
            s1 = 0
        elif name.endswith('2'):
            s2 = 0
        i = np.arange(-s1,s1+1) #-3 ~ 3
        j = np.arange(-s2,s2+1) #-3 ~ 3 
        ii, jj = np.meshgrid(i, j, sparse=True,indexing='ij')
        nu = np.exp(-(ii**2 + jj**2) / (2*tau**2))
        nu[nu < eps] = 0
        nu /= nu.sum()
    
    elif name.startswith('exponential'):
        if name.endswith('1'):
            s1 = 0
            s2 = 20
        elif name.endswith('2'):
            s1 = 20
            s2 = 0
        else:
            s1 = 20
            s2 = 20
        tau = 2
        x = np.arange(-s1,s1+1,1)
        y= np.arange(-s2,s2+1,1)
        xx, yy = np.meshgrid(x,y, indexing = 'ij')
        nu = np.exp(-1 * np.sqrt(xx**2+yy**2) / tau)
        nu[nu <= eps] = 0
        nu = nu / nu.sum()
        
    elif name.startswith('box'):
        if name.endswith('1'):
            x = np.arange(0,1,1)
            y = np.arange(-tau,tau+1,1)
            
        elif name.endswith('2'):
            x = np.arange(-tau,tau+1,1)
            y = np.arange(0,1,1)
            
        else:
            x = np.arange(-tau,tau+1,1)
            y = np.arange(-tau,tau+1,1)
        xx, yy = np.meshgrid(x,y, indexing = 'ij')
        nu = np.exp(0 * (xx + yy))
        nu = nu / nu.sum()
    
    elif name is 'grad1_forward':
        nu = np.zeros((3,1))
        nu[1,0] = -1
        nu[2,0] = 1
        
    elif name is 'grad1_backward':
        nu = np.zeros((3,1))
        nu[0,0] = -1
        nu[1,0] = 1
        
    elif name is 'grad2_forward':
        nu = np.zeros((1,3))
        nu[0,1] = -1
        nu[0,2] = 1
        
    elif name is 'grad2_backward':
        nu = np.zeros((1,3))
        nu[0,0] = -1
        nu[0,1] = 1
        
    elif name is 'laplacian1':
        nu = np.zeros((3,1))
        nu[0,0] = 1
        nu[1,0] = -2
        nu[2,0] = 1
        
    elif name is 'laplacian2':
        nu = np.zeros((1,3))
        nu[0,0] = 1
        nu[0,1] = -2
        nu[0,2] = 1
    
    elif name is 'motion':
        nu = np.load('../assets/motionblur.npy')
        
    else:
        raise('Argument in kernel function is illegal.')
        
    return nu

def show(x, ax=None, vmin=0, vmax=1, *args, **kargs):
    """ Display an image

    Like `~matplotlib.pyplot.imshow` but without showing axes, and
    the range [vmin, vmax] is also effective for RGB images.
    Use grayscale colormap for scalar images.

    Parameters
    ----------
    x : array-like
        An image, float, of shapes (M, N), (M, N, 3) or (M, N, 4)
    ax : a `~matplotlib.axes.Axes` object, optional
        Axes on which to display the image. If not given, current instance.
    vmin, vmax: scalars, optional
        Define the data range that the colormap covers.
        For scalar images, black is vmin and white is vmax.
        For RGB images, black is [vmin, vmin, vmin] and red is [vmax, vmin, vmin].
        By default the range is [0, 1].

    Returns
    -------
    image : `~matplotlib.image.AxesImage`

    Notes
    -----
    All other optional arguments are transfered to matplotlib.pyplot.imshow.

    Copyright Charles Deledalle, 2019
    """

    ax = plt.gca() if ax is None else ax
    x = x.copy().squeeze()
    if vmin is not None:
        x[x < vmin] = vmin
    if vmax is not None:
        x[x > vmax] = vmax
    if x.ndim == 2:
        h = ax.imshow(x, cmap=plt.gray(), vmin=vmin, vmax=vmax, *args, **kargs)
    else:
        vmin = x.min() if vmin is None else vmin
        vmax = x.max() if vmax is None else vmax
        x = (x - vmin) / (vmax - vmin)
        h = ax.imshow(x, vmin=0, vmax=1, *args, **kargs)
    ax.axis('off')
    return h


def showfft(x, ax=None, vmin=None, vmax=None, apply_fft=False, apply_log=False, *args, **kargs):
    """ Display the amplitude of an image spectrum (Fourier transform).

    The zero-frequency is centered. Spectrum is normalized by the image size.
    Both axes are numbered by their corresponding frequencies. Grid is displayed.
    By default, the color map range is optimized for visualization.

    Parameters
    ----------
    x : array-like
        The 2d spectrum of an image, complex, of shapes (M, N), (M, N, 3) or (M, N, 4)
    ax : a `~matplotlib.axes.Axes` object, optional
        Axes on which to display the image spectrum. If not given, current instance.
    apply_fft: boolean, optional
        If True, input x is replaced by `~numpy.fft.fft2(x)`. Default, False.
    apply_log: boolean, optional
        If True, the log of the amplitude is displayed instead.
    vmin, vmax: scalars, optional
        Define the data range that the colormap covers.
        If apply_log=False, by default the range is [0, MAX] where MAX is the maximum
        value of the amplitude of the spectrum. If apply_log=True, by default the
        range is [LMAX-16, LMAX] where LMAX is the maximum value of the log amplitude
        of the spectrum.

    Returns
    -------
    image : `~matplotlib.image.AxesImage`

    Notes
    -----
    All other optional arguments are transfered to matplotlib.pyplot.imshow.

    Copyright Charles Deledalle, 2019
    """

    ax = plt.gca() if ax is None else ax
    n1, n2 = x.shape[:2]
    xpos = np.linspace(0, n2-1, n2)
    xfreq = npf.fftshift(npf.fftfreq(n2, d=1./n2))
    ypos = np.linspace(0, n1-1, n1)
    yfreq = npf.fftshift(npf.fftfreq(n1, d=1./n1))
    x[np.isinf(x)] = x[np.logical_not(np.isinf(x))].max()

    def on_lims_change(axes):
        xlim = axes.get_xlim()
        ylim = axes.get_ylim()
        xsubidx = np.linspace(xlim[0]+1.5, xlim[1]-.5, 9).astype(np.int)
        ysubidx = np.linspace(ylim[0]-.5, ylim[1]+1.5, 9).astype(np.int)
        axes.set_xticks([xpos[i] for i in xsubidx])
        axes.set_yticks([ypos[i] for i in ysubidx])
        axes.set_xticklabels(['%d' % xfreq[i] for i in xsubidx])
        axes.set_yticklabels(['%d' % yfreq[i] for i in ysubidx])

    data = np.abs(npf.fft2(x, axes=(0, 1)) if apply_fft else x) / (n1 * n2)
    data = np.log(data) if apply_log else data
    h = show(npf.fftshift(data),
             vmin=(data.max() - 16 if apply_log else 0) if vmin is None else vmin,
             vmax=data.max() if vmax is None else vmax, ax=ax,
             * args, **kargs)
    ax.axis('on')
    ax.callbacks.connect('xlim_changed', on_lims_change)
    ax.callbacks.connect('ylim_changed', on_lims_change)
    on_lims_change(ax)
    ax.grid(color='r', alpha=.4, linestyle='-', linewidth=.5)
    return h


def kernel2fft(nu, n1, n2, separable=None):
    '''
    Fast Fourier Transform for kernel
    
    Parameters
    ----------
    nu : numpy array
        kernel in time domain
    n1 : int
        image width
    n2 : int
        image length
    separable : str
        option for differnet kinds of transform
        
    Returns
    -------
    lbd : numpy array
        kernel in frequency domain
    '''
    if separable == 'product':
        lbd = (kernel2fft(nu[0], n1, n2), kernel2fft(nu[1], n1, n2))
              
    else:
        tmp = np.zeros((n1,n2))
        s1 = int((nu.shape[0] - 1) / 2)
        s2 = int((nu.shape[1] - 1) / 2)

        tmp = np.zeros((n1,n2))
        tmp[:s1+1, :s2+1] = nu[s1:2*s1+1, s2:2*s2+1]
        tmp[n1-s1:n1, :s2+1] = nu[:s1,s2:2*s2+1]
        tmp[n1-s1:n1,n2-s2:n2] = nu[:s1,:s2]
        tmp[:s1+1,n2-s2:n2] = nu[s1:2*s1+1,:s2]

        lbd = npf.fft2(tmp)
            
    return lbd


    
def add_gaussian_noise(img, sigma):
    '''
    Add gaussian noise on image
    
    Parameters
    ----------
    img : numpy array
        original image
    sigma : float
        standard deviation sigma of gaussian noise
        
    Returns
    -------
    noisy_img : numpy array
        noisy image which is composed of img and guassian noise with standard deviation sigma
    '''
    sig = sigma
    noisy_img = img + sig * np.random.randn(*img.shape)
    noisy_img[noisy_img < 0] = 0
    noisy_img[noisy_img > 1] = 1
    return noisy_img

def convolve(x, nu, boundary = 'periodical', separable=None):
    '''
    Convolution function
    
    Parameters
    ----------
    x : numpy array
        original image
    nu : numpy array
        kernel function
    boundary : str
        option for different kinds of boundary mode
    separable : 'str'
        option for convolution separably or not
        
    Returns
    -------
    xconv : numpy array
        image after convolution
    '''
    if separable is 'product':
        tmp = convolve(x,nu[0],boundary)
        xconv = convolve(tmp,nu[1],boundary)

    elif separable is 'sum':
        tmp1 = convolve(x,nu[0],boundary)
        tmp2 = convolve(x,nu[1],boundary)
        xconv = tmp1+tmp2
        
    else:
        xconv = np.zeros(x.shape)
        s1 = int((nu.shape[0] - 1) / 2)
        s2 = int((nu.shape[1] - 1) / 2)
        for k in range(-s1, s1+1):
            for l in range(-s2, s2+1):
                xconv += nu[k+s1,l+s2]*shift(x,k,l,boundary)
                
    return xconv

def psnr(x, x0):
    '''
    Compute peak signal noise ratio
    
    Parameters
    ----------
    x0 : numpy array 
        original image
    x : numpy array
        denoised image
        
    Returns
    -------
    ans : float
        psnr for x and x0 and its unit is dB
    '''
    R = 255 if np.any(x0>1) else 1
    n = x.size
    ans = 10*np.log10(R**2/(np.linalg.norm(x-x0)**2/n))
    return ans

def imadjust(x,a,b,c,d,gamma=1):
    '''
    Similar to imadjust in MATLAB.
    Converts an image range from [a,b] to [c,d].
    The Equation of a line can be used for this transformation:
        y=((d-c)/(b-a))*(x-a)+c
    However, it is better to use a more generalized equation:
        y=((x-a)/(b-a))^gamma*(d-c)+c
    If gamma is equal to 1, then the line equation is used.
    When gamma is not equal to 1, then the transformation is not linear.
    
    Parameters
    ----------
    x : numpy array
        original image
    a : int/float
        lower bound of x
    b : int/float
        upper bound of x
    c : int/float
        lower bound for new image
    d : int/float
        upper bound for new image
    gamma : int/float
        parameter for equation mentioned above
    
    Returns
    -------
    y : numpy array
        image after adjustment
    '''
    y = (((x - a) / (b - a)) ** gamma) * (d - c) + c
    return y

def cam(cap, nu, lbd, mpsd, sigma):
    '''
    camera function used for capture, reading and apply wiener filter/wiener deconvolution
    
    Parameters
    ----------
    cap : cv2.VideoCapture
        object for capture webcam info
    nu : numpy array
        kernel for convolution
    lbd : numpy array
        kernel in frequency domain
    mpsd : numpy array
        mean power spectral density
    sigma : float
        standard deviation sigma
        
    Returns
    -------
    result : numpy array
        concatenated image (original, noisy, blurry, deblur)
    '''
    ret, frame = cap.read()
    sig = sigma
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    img = imadjust(frame,0,255,0,1,gamma=1)
    noise_img = add_gaussian_noise(img, sig)
    blur_img = denoise(noise_img,lbd[:,:,None],sig)
    blur_img_gau = convolve(img, nu, boundary = 'periodical', separable='product')
    w_decon, transfer = deconvolve_wiener(blur_img_gau, lbd, 1/255, mpsd, return_transfer=True)

    blur_dB = psnr(blur_img,img)
    noise_dB = psnr(noise_img,img)
    
    w_decon[w_decon>1] = 1
    w_decon[w_decon<0] = 0

    result = np.concatenate((img,noise_img,blur_img_gau,w_decon), axis=1)

    print('Noise:{} dB, Denoise:{} dB'.format(noise_dB, blur_dB))
    return result



