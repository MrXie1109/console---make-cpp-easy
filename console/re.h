#pragma once
#include <regex>
#include <string>
#include <vector>

namespace console
{
    class Regex
    {
    private:
        std::regex pattern;

    public:
        Regex(const std::string &pat,
              std::regex::flag_type flags = std::regex::ECMAScript)
            : pattern(pat, flags) {}

        class Match
        {
        private:
            std::smatch match;
            bool success;

        public:
            Match() : success(false) {}
            Match(const std::smatch &m) : match(m), success(true) {}

            std::string group(int n = 0) const
            {
                if (!success || n < 0 || n >= int(match.size()))
                {
                    return "";
                }
                return match[n].str();
            }

            std::vector<std::string> groups() const
            {
                std::vector<std::string> result;
                if (!success)
                    return result;
                for (size_t i = 1; i < match.size(); ++i)
                {
                    result.push_back(match[i].str());
                }
                return result;
            }

            int start(int n = 0) const
            {
                if (!success || n < 0 || n >= int(match.size()))
                {
                    return -1;
                }
                return match.position(n);
            }

            int end(int n = 0) const
            {
                if (!success || n < 0 || n >= int(match.size()))
                {
                    return -1;
                }
                return match.position(n) + match.length(n);
            }

            std::pair<int, int> span(int n = 0) const
            {
                return {start(n), end(n)};
            }

            explicit operator bool() const { return success; }
        };

        Match search(const std::string &text) const
        {
            std::smatch match;
            if (std::regex_search(text, match, pattern))
            {
                return Match(match);
            }
            return Match();
        }

        Match match(const std::string &text) const
        {
            std::smatch match;
            if (std::regex_match(text, match, pattern))
            {
                return Match(match);
            }
            return Match();
        }

        Match fullmatch(const std::string &text) const
        {
            return match(text);
        }

        std::vector<std::string> findall(const std::string &text) const
        {
            std::vector<std::string> result;
            auto begin = std::sregex_iterator(
                text.begin(), text.end(), pattern);
            auto end = std::sregex_iterator();

            for (auto it = begin; it != end; ++it)
            {
                result.push_back(it->str());
            }
            return result;
        }

        class Iterator
        {
        private:
            std::sregex_iterator it;
            std::sregex_iterator end;

        public:
            Iterator(std::sregex_iterator i, std::sregex_iterator e)
                : it(i), end(e) {}

            bool operator!=(const Iterator &other) const
            {
                return it != other.it;
            }
            void operator++() { ++it; }

            Match operator*() const
            {
                return Match(*it);
            }
        };

        Iterator finditer(const std::string &text) const
        {
            return Iterator(
                std::sregex_iterator(text.begin(), text.end(), pattern),
                std::sregex_iterator());
        }

        std::vector<std::string> split(const std::string &text,
                                       int maxsplit = 0) const
        {
            std::vector<std::string> result;
            std::sregex_token_iterator it(text.begin(), text.end(), pattern, -1);
            std::sregex_token_iterator end;

            int count = 0;
            for (; it != end && (maxsplit <= 0 || count < maxsplit);
                 ++it, ++count)
            {
                result.push_back(*it);
            }

            if (maxsplit > 0 && count == maxsplit && it != end)
            {
                std::string remaining;
                for (; it != end; ++it)
                {
                    if (!remaining.empty())
                        remaining += *it;
                    else
                        remaining = *it;
                }
                result.push_back(remaining);
            }

            return result;
        }

        std::string sub(const std::string &repl,
                        const std::string &text, int count = 0) const
        {
            if (count <= 0)
            {
                return std::regex_replace(text, pattern, repl);
            }

            std::string result;
            auto begin = std::sregex_iterator(
                text.begin(), text.end(), pattern);
            auto end = std::sregex_iterator();
            auto last = text.begin();
            int replaced = 0;

            for (auto it = begin;
                 it != end && replaced < count;
                 ++it, ++replaced)
            {
                result.append(last, text.begin() + it->position());
                result.append(repl);
                last = text.begin() + it->position() + it->length();
            }
            result.append(last, text.end());

            return result;
        }

        std::pair<std::string, int> subn(const std::string &repl,
                                         const std::string &text,
                                         int count = 0) const
        {
            if (count <= 0)
            {
                auto result = std::regex_replace(text, pattern, repl);
                auto begin = std::sregex_iterator(
                    text.begin(), text.end(), pattern);
                auto end = std::sregex_iterator();
                int cnt = std::distance(begin, end);
                return {result, cnt};
            }

            std::string result;
            auto begin = std::sregex_iterator(
                text.begin(), text.end(), pattern);
            auto end = std::sregex_iterator();
            auto last = text.begin();
            int replaced = 0;

            for (auto it = begin;
                 it != end && replaced < count;
                 ++it, ++replaced)
            {
                result.append(last, text.begin() + it->position());
                result.append(repl);
                last = text.begin() + it->position() + it->length();
            }
            result.append(last, text.end());

            return {result, replaced};
        }
    };

    namespace re
    {
        inline Regex compile(const std::string &pattern,
                             std::regex::flag_type flags = std::regex::ECMAScript)
        {
            return Regex(pattern, flags);
        }

        inline Regex::Match search(const std::string &pattern,
                                   const std::string &text)
        {
            return Regex(pattern).search(text);
        }

        inline Regex::Match match(const std::string &pattern,
                                  const std::string &text)
        {
            return Regex(pattern).match(text);
        }

        inline std::vector<std::string> findall(const std::string &pattern,
                                                const std::string &text)
        {
            return Regex(pattern).findall(text);
        }

        inline std::vector<std::string> split(const std::string &pattern,
                                              const std::string &text,
                                              int maxsplit = 0)
        {
            return Regex(pattern).split(text, maxsplit);
        }

        inline std::string sub(const std::string &pattern,
                               const std::string &repl,
                               const std::string &text, int count = 0)
        {
            return Regex(pattern).sub(repl, text, count);
        }

        inline std::string escape(const std::string &s)
        {
            static std::regex special(R"([.^$*+?()\[\]{}|\\])");
            return std::regex_replace(s, special, R"(\$&)");
        }
    }
}
