import tornado.ioloop
import tornado.web


#定义一个类，继承tornado.web.RequestHandler
class MainHandler(tornado.web.RequestHandler):
    def get(self):
        print(self.get_browser_locale())
        print("get!!!")
        self.write("Hello, world")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
    ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8888)
    tornado.ioloop.IOLoop.current().start()