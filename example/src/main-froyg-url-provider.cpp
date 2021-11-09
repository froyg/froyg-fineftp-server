#include <fineftp/server.h>
#include <fineftp/froyg-url-provider.h>

#include <iostream>
#include <memory>
#include <thread>
#include <string>

class OurUrlProvider : public froyg::UrlProvider
{
public:
  bool can_handle_path(const std::string& url)
  {
    std::cout << "URL: " << url << std::endl;
    if (url == "/blah") {
      return true;
    } else {
      return false;
    }
  }

  std::shared_ptr<std::vector<char>> get_content(const std::string& url)
  {
    auto data = std::make_shared<std::vector<char>>();
    for (int i = 0; i < 10; i++) {
      data->push_back('a');
    }
    return data;
  }
};

int
main()
{

#ifdef WIN32
  std::string local_root = "C:\\"; // The backslash at the end is necessary!
#else                              // WIN32
  std::string local_root = "/";
#endif                             // WIN32

  OurUrlProvider url_provider;

  // Create an FTP Server on port 2121. We use 2121 instead of the default
  // port 21, as your application would need root privileges to open port 21.
  fineftp::FtpServer server(&url_provider, 2121);

  // Add the well known anonymous user and some normal users. The anonymous
  // user can log in with username "anonyous" or "ftp" and any password. The
  // normal users have to provide their username and password.
  server.addUserAnonymous(local_root, fineftp::Permission::All);
  server.addUser(
    "MyUser", "MyPassword", local_root, fineftp::Permission::ReadOnly);
  server.addUser(
    "Uploader", "123456", local_root,
    fineftp::Permission::DirList | fineftp::Permission::DirCreate |
      fineftp::Permission::FileWrite | fineftp::Permission::FileAppend);

  // Start the FTP server with 4 threads. More threads will increase the
  // performance with multiple clients, but don't over-do it.
  server.start(4);

  // Prevent the application from exiting immediatelly
  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
