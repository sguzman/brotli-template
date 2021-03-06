#include <iostream>
#include "./include/crow.h"
#include "http_get.hxx"

using std::cout;
using std::cerr;
using std::endl;

constexpr static const char * const address{"0.0.0.0"};
constexpr const static unsigned short cores{8};

static inline const crow::response resp(
    const std::string& user,
    const std::string& repo,
    const std::string& branch,
    const std::string& folder,
    const std::string& file) noexcept {
  std::string url{"https://raw.githubusercontent.com/"};
  {
    url += user;
    url += "/";
    url += repo;
    url += "/";
    url += branch;
    url += "/";
    url += folder;
    url += "/";
    url += file;
  }

  auto& body = Curl::get(url);
  crow::response response{crow::response(200, body)};
  {
    response.add_header("Content-Encoding", "br");
    response.add_header("Access-Control-Allow-Origin", "*");
    response.add_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  }

  return response;
}

int main(int, char*[], char* env[]) noexcept {
  unsigned short port{0};
  {
    char port_str[5]{};
    for (char** e{env}; *e != nullptr; ++e) {
      char* str{*e};
      if (str[0] == 'P' && str[1] == 'O' && str[2] == 'R' && str[3] == 'T' && str[4] == '=') {
        for (uint8_t i{5}; str[i] != '\0'; ++i) {
          port_str[i - 5] = str[i];
        }

        port = static_cast<unsigned short>(atoi(port_str));
        cout << "Found PORT env var with val " << port << endl;

        break;
      }
    }
  }

  if (port == 0) {
    port = 8080;
    cout << "Defaulting to port " << port << endl;
  }

  {
      crow::SimpleApp app{};
      CROW_ROUTE(app, "/<string>/<string>/<string>/<string>/<string>")(resp);

      app
          .port(port)
          .bindaddr(address)
          .concurrency(cores)
          .multithreaded()
          .run();
  }

  return EXIT_SUCCESS;
}