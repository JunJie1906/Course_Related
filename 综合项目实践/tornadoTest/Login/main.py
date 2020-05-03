import tornado.httpserver
import tornado.ioloop
import tornado.web
import tornado.options
import os.path

from tornado.options import define, options

define("port", default=8000, help="run on the given port", type=int)


class BaseHandler(tornado.web.RequestHandler):
    def get_current_user(self):
        return self.get_secure_cookie("username")


class LoginHandler(BaseHandler):
    def get(self):
        self.render('login.html')

    def post(self):
        if self.get_argument("username")=="root" and self.get_argument("password")=="123456":
            self.set_secure_cookie("username", self.get_argument("username"))
            self.redirect("/")
        else:
            self.write("<script>alert(\"用户名或密码错误\")</script>")
            self.render("login.html")


class WelcomeHandler(BaseHandler):
    @tornado.web.authenticated
    def get(self):
        self.render('index.html', username=self.current_user)


class LogoutHandler(BaseHandler):
    def post(self):
        if (self.get_argument("logout", None)):
            self.clear_cookie("username")
        self.redirect("/")


if __name__ == "__main__":
    tornado.options.parse_command_line()
    settings = {
        "template_path": os.path.join(os.path.dirname(__file__), "templates"),
        "cookie_secret": "jHGJHGFKHJGJHgjhgjAS",
        "login_url": "/login",
        'cookie': {
            'expires_days': 1,
            'max_age': 100
        },


    }
    application = tornado.web.Application([
        (r'/', WelcomeHandler),
        (r'/login', LoginHandler),
        (r'/logout', LogoutHandler)
    ], debug=True, **settings)
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
