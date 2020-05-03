import ffmpeg
import numpy as np
import subprocess as sp
import threading
import queue
import time
class CCTVReader():
    def __init__(self, queue):
        super().__init__()
        self.queue = queue
        self.command = ["ffmpeg",  "-y",
                        "-hwaccel",  "nvdec",
                        "-c:v",  "h264_cuvid",
                        "-vsync", "0",
                        "-max_delay", "500000",
                        "-reorder_queue_size", "10000",
                        "-i",  "rtsp://xxx.xxx.xxx.xxx:xxx/Streaming/Channels/101?transportmode=multicast",
                        "-pix_fmt", "yuv420p",
                        "-preset", "slow",
                        "-an", "-sn",
                        "-vf", "fps=29",
                        "-"]
    def run(self):
        pipe = sp.Popen(self.command, stdout = sp.PIPE, bufsize=1024**3, shell=True)
        timer = time.time()
        counter = 0
        while True:
            self.queue.put(pipe.stdout.read(int(1280*720*6//4)))


c = CCTVReader()
c.run()