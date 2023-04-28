#ifndef RAYTRACER_INCLUDE_SYNTAX_HIGHLIGHTING_HPP
#define RAYTRACER_INCLUDE_SYNTAX_HIGHLIGHTING_HPP

#include <parser.hpp>

#include <cinttypes>
#include <array>
#include <iostream>
#include <map>
#include <stack>
#include <sstream>
#include "parser/tuple.hpp"


class SyntaxHighlighter {
public:
	class SymbolNotFound : public std::exception {
	public:
		const char *what() const noexcept override {
			return message.c_str();
		}


	private:
		explicit SymbolNotFound(const std::string &tok) {
			std::ostringstream oss;

			oss << "token `" << tok << "` has no correspondence with a known symbol";
			message = oss.str();
		}


		friend class SyntaxHighlighter;

		std::string message;
	};

	SyntaxHighlighter(std::ostream &out = std::cout);
	SyntaxHighlighter(const SyntaxHighlighter &other) = delete;
	SyntaxHighlighter &operator=(const SyntaxHighlighter &other) = delete;
	~SyntaxHighlighter();

	typedef SyntaxHighlighter &(*sh_manipulator)(SyntaxHighlighter &);

	SyntaxHighlighter &operator<<(const std::string &tok);
	SyntaxHighlighter &operator<<(double tok);
	SyntaxHighlighter &operator<<(long tok);
	friend SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, sh_manipulator fn);
	SyntaxHighlighter &operator<<(uint8_t tok);

	static SyntaxHighlighter &endl(SyntaxHighlighter &sh);
	static SyntaxHighlighter &end(SyntaxHighlighter &sh);

private:

	struct ci_less {
		// case-independent (ci) compare_less binary function
		struct nocase_compare {
			bool operator()(const unsigned char &c1, const unsigned char &c2) const {
				return tolower(c1) < tolower(c2);
			}
		};


		bool operator()(const std::string &s1, const std::string &s2) const {
			return std::lexicographical_compare
					(s1.begin(), s1.end(),   // source range
					 s2.begin(), s2.end(),   // dest range
					 nocase_compare());  // comparison
		}
	};

	enum symbol_category {
		CLEAR   = -2,
		UNKNOWN = -1,
		PUNCTUATION,
		BLOCK_TUPLE_DELIMITATION,
		BLOCK_KEYWORD,
		BLOCK_IDENTIFIER,
		LINE_KEYWORD,
		SCALAR,
	};

	typedef yy::parser::symbol_kind_type                symbol_kind;
	typedef std::map<std::string, symbol_kind, ci_less> str_symbol_mapper;
	typedef std::map<symbol_category, std::string>      symbol_color_mapper;

	static const str_symbol_mapper symbols;
	static str_symbol_mapper init_symbols();

	static const symbol_color_mapper colors;
	static symbol_color_mapper init_colors();

	std::string get_after_whitespace(symbol_kind kind, symbol_category cat, std::string &indent);

	static symbol_kind get_kind(const std::string &tok);
	static symbol_kind get_kind(double tok);
	static symbol_kind get_kind(long tok);
	static symbol_kind get_kind(uint8_t tok);

	symbol_category get_symbol_category(symbol_kind kind) const;

	void update_state(SyntaxHighlighter::symbol_kind kind, SyntaxHighlighter::symbol_category cat);
	void update_accepting_for_current_block();

	static std::string stringify_keyword(symbol_kind kind, symbol_category cat);

	symbol_kind             accepting;
	symbol_kind             last_sym;
	std::stack<symbol_kind> blocks;
	static const size_t     indentation_increment = 4;


	std::ostream &os;
};


template<typename T, size_t size>
SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Tuple<T, size> &t) {
	sh << "(";
	if (!t.empty()) {
		sh << t[0];
		for (size_t i = 1; i < t.size(); i++)
			sh << "," << t[i];
	}

	return sh << ")";
}


#endif //RAYTRACER_INCLUDE_SYNTAX_HIGHLIGHTING_HPP
