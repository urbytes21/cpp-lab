#include <iterator>
#include <regex>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
void run() {
  const std::string text =
      "This is my string. "
      "I'll use regular expression. "
      "Now I have two problems.";
  LOG("String: " + text);

  // Case-insensitive search
  // Match any part
  const std::regex regex_search_exp(R"(regular expression)",
                                    std::regex_constants::icase);

  if (std::regex_search(text, regex_search_exp)) {
    LOG("\tString contains 'regular expression'");
  }

  // Phone validation
  // Match entire
  const std::string phone = "+84336821417";
  const std::regex phone_regex(R"(^[+](?:[0-9\-\(\)/\.]\s?){6,15}[0-9]$)");
  if (!std::regex_match(phone, phone_regex)) {
    throw std::invalid_argument(
        "Invalid phone number format. "
        "Try including the country code.");
  }

  // Word matching
  LOG("Find words: ");
  const std::regex word_regex(R"((\w+))");
  auto words_begin = std::sregex_iterator(
      text.begin(), text.end(),
      word_regex);  // iterator over regex matches in a string
  auto words_end = std::sregex_iterator();

  LOG_S("\tFound " << std::distance(words_begin, words_end) << " words");

  LOG("Find words longer than 5 chars: ");
  for (auto it = std::sregex_iterator(text.begin(), text.end(), word_regex);
       it != words_end; ++it) {
    const std::string word = it->str();

    if (word.size() > 5) {
      LOG("\t" + word);
    }
  }

  // Replace long words
  LOG("Replace \"long_words\" to : \"[long_words]\"");
  const std::regex long_word_regex(R"((\w{5,}))");
  const std::string highlighted =
      std::regex_replace(text, long_word_regex, "[$&]");  // "$&": entire match

  LOG("\t" + highlighted);
}
}  // namespace

class Regex : public IExample {
 public:
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "Regex"; }
  std::string description() const override {
    return "The examples for regular expression <regex>";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(Regex);