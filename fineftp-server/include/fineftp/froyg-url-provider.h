
#ifndef FROYG_URL_PROVIDER
#define FROYG_URL_PROVIDER

#include <string>
#include <memory>
#include <vector>

namespace froyg
{
class UrlProvider
{
public:
  virtual bool can_handle_path(const std::string& url) = 0;
  virtual std::shared_ptr<std::vector<char>> get_content(
    const std::string& url) = 0;
};
} // namespace froyg

#endif
