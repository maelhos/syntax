/**
 * LR parser for C++ generated by the Syntax tool.
 *
 * https://www.npmjs.com/package/syntax-cli
 *
 *   npm install -g syntax-cli
 *
 *   syntax-cli --help
 *
 * To regenerate run:
 *
 *   syntax-cli \
 *     --grammar ~/path-to-grammar-file \
 *     --mode <parsing-mode> \
 *     --output ~/ParserClassName.h
 */
#ifndef __Syntax_LR_Parser_h
#define __Syntax_LR_Parser_h

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"

#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace syntax {

// ------------------------------------
// Module include prologue.
//
// Should include at least value/result type:
//
// type Value = <...>;
//
// Or struct Value { ... };
//
// Can also include parsing hooks:
//
//   void onParseBegin(const Parser& parser, const std::string& str) {
//     ...
//   }
//
//   void onParseBegin(const Parser& parser, const Value& result) {
//     ...
//   }
//
// clang-format off
{{{MODULE_INCLUDE}}}  // clang-format on

/**
 * Tokenizer class.
 */
// clang-format off
{{{TOKENIZER}}}
// clang-format on

/**
 * Parsing table type.
 */
enum class TE {
  Accept,
  Shift,
  Reduce,
  Transit,
};

/**
 * Parsing table entry.
 */
struct TableEntry {
  TE type;
  int value;
};

/**
 * Encoded production.
 *
 * opcode - encoded index
 * rhsLength - length of the RHS to pop.
 */
struct Production {
  int opcode;
  int rhsLength;
};

// Key: Encoded symbol (terminal or non-terminal) index
// Value: TableEntry
using Row = std::map<int, TableEntry>;

/**
 * Base class for the parser.
 */
class yyparse {
 public:
  /**
   * Parsing values stack.
   */
  std::stack<Value> valuesStack;

  /**
   * Token values stack.
   */
  std::stack<std::string> tokensStack;

  /**
   * Parsing states stack.
   */
  std::stack<int> statesStack;

  /**
   * Previous state to calculate the next one.
   */
  int previousState;

 private:
  // clang-format off
  static constexpr size_t PRODUCTIONS_COUNT = {{{PRODUCTIONS_COUNT}}};
  static std::array<Production, PRODUCTIONS_COUNT> productions_;

  static constexpr size_t ROWS_COUNT = {{{ROWS_COUNT}}};
  static std::array<Row, ROWS_COUNT> table_;
  // clang-format on
};

// ------------------------------------------------------------------
// Productions.

// clang-format off
std::array<Production, yyparse::PRODUCTIONS_COUNT> yyparse::productions_ = {{{PRODUCTIONS}}};
// clang-format on

#define POP_V()             \
  parser.valuesStack.top(); \
  parser.valuesStack.pop()

#define POP_T()             \
  parser.tokensStack.top(); \
  parser.tokensStack.pop()

#define PUSH_VR() parser.valuesStack.push(__)
#define PUSH_TR() parser.tokensStack.push(__)

#define CAPTURE_STATE()                            \
  parser.previousState = parser.statesStack.top(); \
  parser.statesStack.pop()

// clang-format off
{{{PRODUCTION_HANDLERS}}}
// clang-format on

// ------------------------------------------------------------------
// Parsing table.

// clang-format off
std::array<Row, yyparse::ROWS_COUNT> yyparse::table_ = {{{TABLE}}};
// clang-format on

}  // namespace syntax

#endif