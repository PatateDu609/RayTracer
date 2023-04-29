#include "syntax_highlighting.hpp"
#include <iomanip>
#include <regex>

const static std::regex exp("^[a-z][a-z0-9A-Z_]*$");


const SyntaxHighlighter::str_symbol_mapper   SyntaxHighlighter::symbols = init_symbols();
const SyntaxHighlighter::symbol_color_mapper SyntaxHighlighter::colors  = init_colors();


SyntaxHighlighter::symbol_category SyntaxHighlighter::get_symbol_category(symbol_kind kind) const {
	switch (kind) {
		case symbol_kind::S_INT:
		case symbol_kind::S_FLOAT:
			return SCALAR;

		case symbol_kind::S_ID:
			return BLOCK_IDENTIFIER;

		case symbol_kind::S_OPEN_BLOCK:
		case symbol_kind::S_CLOSE_BLOCK:
		case symbol_kind::S_OPEN_TUPLE:
		case symbol_kind::S_CLOSE_TUPLE:
			return BLOCK_TUPLE_DELIMITATION;

		case symbol_kind::S_COMMA:
		case symbol_kind::S_EQUAL:
			return PUNCTUATION;

		case symbol_kind::S_POINT_LIGHT:
		case symbol_kind::S_AMBIENT_LIGHT:
		case symbol_kind::S_CAMERA:
		case symbol_kind::S_SPHERE:
			return BLOCK_KEYWORD;

		case symbol_kind::S_MATERIAL: {
			if (accepting == symbol_kind::S_file_object_description)
				return BLOCK_KEYWORD; // We're out of every other block (that can accept materials...)
			return LINE_KEYWORD; // We're in one of these blocks         ↑↑↑↑↑
		}

		case symbol_kind::S_RESOLUTION:
		case symbol_kind::S_POSITION:
		case symbol_kind::S_COLOR:
		case symbol_kind::S_INTENSITY:
		case symbol_kind::S_VIEW_DIRECTION:
		case symbol_kind::S_FOV:
		case symbol_kind::S_RADIUS:
		case symbol_kind::S_DIFFUSE:
			return LINE_KEYWORD;

		default:
			return UNKNOWN;
	}
}


#define STR(x) #x
#define MAKE_ANSI(code) "\033[38;5;" STR(code) "m"
#define MAKE_BOLD_ANSI(code) "\033[1;38;5;" STR(code) "m"


SyntaxHighlighter::symbol_color_mapper SyntaxHighlighter::init_colors() {
	symbol_color_mapper mapping;

	mapping[CLEAR]   = "\033[0m";
	mapping[UNKNOWN] = mapping[CLEAR] + "\033[48;5;124m\033[4m"; // Underline, background red...

	mapping[SCALAR]                   = MAKE_ANSI(158);
	mapping[PUNCTUATION]              = MAKE_ANSI(225);
	mapping[BLOCK_TUPLE_DELIMITATION] = MAKE_ANSI(224);
	mapping[BLOCK_IDENTIFIER]         = mapping[CLEAR]+"\033[4m" + MAKE_ANSI(104);
	mapping[BLOCK_KEYWORD]            = MAKE_BOLD_ANSI(99);
	mapping[LINE_KEYWORD]             = MAKE_BOLD_ANSI(202);

	return mapping;
}


SyntaxHighlighter::str_symbol_mapper SyntaxHighlighter::init_symbols() {
	str_symbol_mapper mapping;

	mapping["INT"]   = symbol_kind::S_INT;
	mapping["FLOAT"] = symbol_kind::S_FLOAT;
	mapping["ID"]    = symbol_kind::S_ID;

	mapping["{"] = symbol_kind::S_OPEN_BLOCK;
	mapping["}"] = symbol_kind::S_CLOSE_BLOCK;
	mapping["("] = symbol_kind::S_OPEN_TUPLE;
	mapping[")"] = symbol_kind::S_CLOSE_TUPLE;
	mapping[","] = symbol_kind::S_COMMA;
	mapping["="] = symbol_kind::S_EQUAL;

	mapping["resolution"]     = symbol_kind::S_RESOLUTION;
	mapping["point_light"]    = symbol_kind::S_POINT_LIGHT;
	mapping["ambient_light"]  = symbol_kind::S_AMBIENT_LIGHT;
	mapping["camera"]         = symbol_kind::S_CAMERA;
	mapping["sphere"]         = symbol_kind::S_SPHERE;
	mapping["position"]       = symbol_kind::S_POSITION;
	mapping["color"]          = symbol_kind::S_COLOR;
	mapping["intensity"]      = symbol_kind::S_INTENSITY;
	mapping["view_dir"] = symbol_kind::S_VIEW_DIRECTION;
	mapping["fov"]            = symbol_kind::S_FOV;
	mapping["material"]       = symbol_kind::S_MATERIAL;
	mapping["radius"]         = symbol_kind::S_RADIUS;
	mapping["diffuse"]        = symbol_kind::S_DIFFUSE;

	return mapping;
}


std::string SyntaxHighlighter::stringify_keyword(symbol_kind kind, symbol_category cat) {
	switch (kind) {
		case symbol_kind::S_RESOLUTION:
			return "resolution";
		case symbol_kind::S_POINT_LIGHT:
			return "Point Light";
		case symbol_kind::S_AMBIENT_LIGHT:
			return "Ambient Light";
		case symbol_kind::S_CAMERA:
			return "Camera";
		case symbol_kind::S_SPHERE:
			return "Sphere";
		case symbol_kind::S_MATERIAL:
			return cat == BLOCK_KEYWORD ? "Material" : "material";
		case symbol_kind::S_POSITION:
			return "position";
		case symbol_kind::S_COLOR:
			return "color";
		case symbol_kind::S_INTENSITY:
			return "intensity";
		case symbol_kind::S_VIEW_DIRECTION:
			return "view direction";
		case symbol_kind::S_FOV:
			return "fov";
		case symbol_kind::S_RADIUS:
			return "radius";
		case symbol_kind::S_DIFFUSE:
			return "diffuse";
		default:
			return "";
	}
}


SyntaxHighlighter::SyntaxHighlighter(std::ostream &out) :
		accepting(symbol_kind::S_file_object_description),
		last_sym(symbol_kind::S_YYACCEPT),
		os(out) {
}

SyntaxHighlighter::~SyntaxHighlighter() {
	os << colors.at(CLEAR);

	os.flush();
	os.clear();
}


std::string SyntaxHighlighter::get_after_whitespace(symbol_kind kind, symbol_category cat, std::string &indent) {
	if (!blocks.empty())
		indent.assign(indentation_increment * (blocks.size() - (kind == symbol_kind::S_CLOSE_BLOCK)), ' ');
	else
		indent.clear();

	if (kind == symbol_kind::S_YYUNDEF && !blocks.empty())
		return indent;
	else if (kind == symbol_kind::S_YYUNDEF)
		return " ";

	switch (cat) {
		case CLEAR:
			return "\n";
		case PUNCTUATION:
			return " ";
		case BLOCK_TUPLE_DELIMITATION: {
			if (kind == symbol_kind::S_OPEN_BLOCK
			    || kind == symbol_kind::S_CLOSE_TUPLE
			    || kind == symbol_kind::S_CLOSE_BLOCK)
				return "\n";
			return "";
		}
		case LINE_KEYWORD:
		case BLOCK_KEYWORD:
		case BLOCK_IDENTIFIER:
			return " ";
		case SCALAR:
			return "";
		case UNKNOWN:
			return "";
	}
	return "";
}


SyntaxHighlighter::symbol_kind SyntaxHighlighter::get_kind(const std::string &tok) {
	try {
		return symbols.at(tok);
	} catch (const std::out_of_range &e) {
		if (std::regex_search(tok, exp))
			return get_kind("ID");

		throw SymbolNotFound(tok);
	}
}


SyntaxHighlighter::symbol_kind SyntaxHighlighter::get_kind(double tok) {
	try {
		return symbols.at("FLOAT");
	} catch (const std::out_of_range &e) {
		throw SymbolNotFound(std::to_string(tok));
	}
}


SyntaxHighlighter::symbol_kind SyntaxHighlighter::get_kind(long tok) {
	try {
		return symbols.at("INT");
	} catch (const std::out_of_range &e) {
		throw SymbolNotFound(std::to_string(tok));
	}
}


SyntaxHighlighter::symbol_kind SyntaxHighlighter::get_kind(uint8_t tok) {
	return get_kind(static_cast<long>(tok));
}


void SyntaxHighlighter::update_accepting_for_current_block() {
	if (blocks.empty()) {
		accepting = symbol_kind::S_file_object_description;
		return;
	}

	symbol_kind current_block = blocks.top();

	switch (current_block) {
		case symbol_kind::S_SPHERE:
			accepting = symbol_kind::S_sphere_block_content;
			break;
		case symbol_kind::S_MATERIAL:
			accepting = symbol_kind::S_material_block_content;
			break;
		case symbol_kind::S_POINT_LIGHT:
			accepting = symbol_kind::S_point_light_block_content;
			break;
		case symbol_kind::S_AMBIENT_LIGHT:
			accepting = symbol_kind::S_ambient_light_block_content;
			break;
		case symbol_kind::S_CAMERA:
			accepting = symbol_kind::S_camera_block_content;
			break;
		default:
			accepting = symbol_kind::S_YYUNDEF;
			break;
	}
}


void SyntaxHighlighter::update_state(SyntaxHighlighter::symbol_kind kind, SyntaxHighlighter::symbol_category cat) {
	switch (kind) {
		case symbol_kind::S_RESOLUTION:
		case symbol_kind::S_POSITION:
		case symbol_kind::S_COLOR:
		case symbol_kind::S_INTENSITY:
		case symbol_kind::S_VIEW_DIRECTION:
		case symbol_kind::S_FOV:
		case symbol_kind::S_RADIUS:
		case symbol_kind::S_DIFFUSE: {
			accepting = symbol_kind::S_EQUAL;
			break;
		}

		case symbol_kind::S_MATERIAL: {
			if (cat == BLOCK_KEYWORD || last_sym == symbol_kind::S_EQUAL) {
				accepting = symbol_kind::S_EQUAL;
				blocks.push(kind);
				break;
			}
			accepting = symbol_kind::S_identifier;
			break;
		}

		case symbol_kind::S_POINT_LIGHT:
		case symbol_kind::S_AMBIENT_LIGHT:
		case symbol_kind::S_CAMERA:
		case symbol_kind::S_SPHERE: {
			accepting = symbol_kind::S_identifier;
			blocks.push(kind);
			break;
		}

		case symbol_kind::S_OPEN_BLOCK:
			update_accepting_for_current_block();
			break;

		case symbol_kind::S_CLOSE_BLOCK:
			blocks.pop();
			update_accepting_for_current_block();
			break;

		default:
			break;
	}
	last_sym = kind;
}


SyntaxHighlighter &SyntaxHighlighter::operator<<(const std::string &ahead) {
	symbol_kind     kind;
	symbol_category cat;
	std::string     ansi_code;

	try {
		kind = get_kind(ahead);
		cat  = get_symbol_category(kind);
	} catch (const SymbolNotFound &e) {
		kind = symbol_kind::S_YYUNDEF;
		cat  = UNKNOWN;
	}

	ansi_code = colors.at(cat);

	std::string indent;
	std::string after = get_after_whitespace(kind, cat, indent);

	if (kind != symbol_kind::S_MATERIAL || last_sym != symbol_kind::S_EQUAL) {
		if (!blocks.empty() && (cat == LINE_KEYWORD || kind == symbol_kind::S_CLOSE_BLOCK))
			std::cout << indent;

		if (cat == BLOCK_KEYWORD || cat == LINE_KEYWORD)
			os << ansi_code << stringify_keyword(kind, cat) << colors.at(CLEAR) << after;
		else
			os << ansi_code << ahead << colors.at(CLEAR) << after;
	}

	update_state(kind, cat);
	return *this;
}


SyntaxHighlighter &SyntaxHighlighter::operator<<(double ahead) {
	symbol_kind     kind;
	symbol_category cat;
	std::string     ansi_code;

	try {
		kind = get_kind(ahead);
		cat  = get_symbol_category(kind);
	} catch (const SymbolNotFound &e) {
		kind = symbol_kind::S_YYUNDEF;
		cat  = UNKNOWN;
	}

	ansi_code = colors.at(cat);
	const auto ss = os.precision();


	std::string indent;
	std::string after = get_after_whitespace(kind, cat, indent);

	if (!blocks.empty() && cat == LINE_KEYWORD)
		std::cout << indent;

	os << ansi_code;
	os << std::setprecision(3) << ahead << std::setprecision(ss);
	os << colors.at(CLEAR) << after;
	return *this;
}


SyntaxHighlighter &SyntaxHighlighter::operator<<(long ahead) {
	symbol_kind     kind;
	symbol_category cat;
	std::string     ansi_code;

	try {
		kind = get_kind(ahead);
		cat  = get_symbol_category(kind);
	} catch (const SymbolNotFound &e) {
		kind = symbol_kind::S_YYUNDEF;
		cat  = UNKNOWN;
	}

	ansi_code = colors.at(cat);

	std::string indent;
	std::string after = get_after_whitespace(kind, cat, indent);

	if (!blocks.empty() && cat == LINE_KEYWORD)
		std::cout << indent;

	os << ansi_code << ahead << colors.at(CLEAR) << after;
	return *this;
}


SyntaxHighlighter &SyntaxHighlighter::operator<<(uint8_t ahead) {
	symbol_kind     kind;
	symbol_category cat;
	std::string     ansi_code;

	try {
		kind = get_kind(ahead);
		cat  = get_symbol_category(kind);
	} catch (const SymbolNotFound &e) {
		kind = symbol_kind::S_YYUNDEF;
		cat  = UNKNOWN;
	}

	ansi_code = colors.at(cat);


	std::string indent;
	std::string after = get_after_whitespace(kind, cat, indent);

	if (!blocks.empty() && cat == LINE_KEYWORD)
		std::cout << indent;

	os << ansi_code << +ahead << colors.at(CLEAR) << after;
	return *this;
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, SyntaxHighlighter::sh_manipulator fn) {
	return fn(sh);
}


SyntaxHighlighter &SyntaxHighlighter::endl(SyntaxHighlighter &sh) {
	sh.os << std::endl;
	return sh;
}


SyntaxHighlighter &SyntaxHighlighter::end(SyntaxHighlighter &sh) {
	sh.os.flush();
	return sh;
}
