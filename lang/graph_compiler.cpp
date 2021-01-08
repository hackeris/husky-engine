//
// Created by rainm on 2021/1/1.
//

#include <cmath>

#include "antlr4-runtime.h"
#include "grammar/HuskyLangLexer.h"
#include "grammar/HuskyLangParser.h"

#include "graph.h"
#include "error_listener.h"
#include "graph_compiler.h"
#include "util/finalize.h"

using namespace antlrcpp;
using namespace husky;

antlrcpp::Any graph_compiler::visitInt(HuskyLangParser::IntContext *context) {
    auto value = (int) std::strtol(context->getText().c_str(), nullptr, 10);
    return Any(literal{value});
}

antlrcpp::Any graph_compiler::visitDouble(HuskyLangParser::DoubleContext *context) {
    auto value = (float) std::strtod(context->getText().c_str(), nullptr);
    return Any(literal{value});
}

antlrcpp::Any graph_compiler::visitConstantE(HuskyLangParser::ConstantEContext *context) {
    auto pi = (float) M_PI;
    return Any(literal{pi});
}

antlrcpp::Any graph_compiler::visitConstantPI(HuskyLangParser::ConstantPIContext *context) {
    auto pi = (float) M_E;
    return Any(literal{pi});
}

antlrcpp::Any graph_compiler::visitIdentifier(HuskyLangParser::IdentifierContext *context) {
    std::string name = context->getText();
    return Any(identifier_ref{std::move(name)});
}

antlrcpp::Any graph_compiler::visitToLiteral(HuskyLangParser::ToLiteralContext *context) {
    return visit(context->literal());
}

antlrcpp::Any graph_compiler::visitToIdentifier(HuskyLangParser::ToIdentifierContext *context) {
    return visit(context->identifier());
}

antlrcpp::Any graph_compiler::visitBraces(HuskyLangParser::BracesContext *context) {
    return visit(context->expression());
}

antlrcpp::Any graph_compiler::visitArrayIndex(HuskyLangParser::ArrayIndexContext *context) {
    const Any &ident = visit(context->identifier());
    const Any &idx = visit(context->expression());
    return Any(array_index(ident.as<identifier_ref>(),
                           idx.as<expression_ptr>()));
}

antlrcpp::Any graph_compiler::visitArgList(HuskyLangParser::ArgListContext *context) {

    Any parsed_args;
    if (context->argList() == nullptr) {
        parsed_args = std::make_shared<std::vector<expression_ptr>>();
    } else {
        parsed_args = visit(context->argList());
    }

    const arg_list &parsed = parsed_args.as<arg_list>();

    const Any &expr = wrap_expression(visit(context->expression()));
    parsed->push_back(expr.as<expression_ptr>());
    return parsed;
}

antlrcpp::Any graph_compiler::visitFuncCall(HuskyLangParser::FuncCallContext *context) {

    const Any &args = visit(context->argList());
    std::string funcName = context->identifier()->getText();

    return function_call(std::move(funcName), args.as<arg_list>());
}

antlrcpp::Any graph_compiler::visitPower(HuskyLangParser::PowerContext *context) {

    const Any &left = visit(context->powr());
    const Any &right = visit(context->atom());

    const std::shared_ptr<atom> &right_atom = wrap_atom(right);

    if (left.is<atom_ptr>()) {
        const std::shared_ptr<atom> &leftAtom = left.as<atom_ptr>();
        return binary_op(binary_op::op_type::op_power,
                         std::make_shared<expression>(leftAtom),
                         std::make_shared<expression>(right_atom));
    } else if (left.is<binary_op>()) {
        const auto &leftPower = left.as<binary_op>();
        return binary_op(binary_op::op_type::op_power,
                         std::make_shared<expression>(leftPower),
                         std::make_shared<expression>(right_atom));
    } else {
        throw std::runtime_error("unexpected left type");
    }
}

antlrcpp::Any graph_compiler::visitToAtom(HuskyLangParser::ToAtomContext *context) {
    const Any &atom_val = visit(context->atom());
    return wrap_atom(atom_val);
}

antlrcpp::Any graph_compiler::visitToPower(HuskyLangParser::ToPowerContext *context) {
    return visit(context->powr());
}

antlrcpp::Any graph_compiler::visitUnaryOp(HuskyLangParser::UnaryOpContext *context) {
    const std::string &opText = context->op->getText();
    unary_op::op_type opType = get_unary_op(opText);

    const Any &operand = visit(context->powr());
    if (operand.is<binary_op>()) {
        return unary_op(opType, operand.as<binary_op>());
    } else if (operand.is<atom_ptr>()) {
        return unary_op(opType, operand.as<atom_ptr>());
    } else {
        throw std::runtime_error("unexpected operand type");
    }
}

antlrcpp::Any graph_compiler::visitMultiDivOp(HuskyLangParser::MultiDivOpContext *context) {
    const expression_ptr &leftExpr = wrap_expression(visit(context->multOrDiv()));
    const expression_ptr &rightExpr = wrap_expression(visit(context->powr()));
    binary_op::op_type opType = get_binary_op(context->op->getText());
    return binary_op(opType, leftExpr, rightExpr);
}

expression_ptr graph_compiler::wrap_expression(const Any &any) {
    if (any.is<expression_ptr>()) {
        return any;
    } else if (any.is<binary_op>()) {
        return std::make_shared<expression>(any.as<binary_op>());
    } else if (any.is<unary_op>()) {
        return std::make_shared<expression>(any.as<unary_op>());
    } else if (any.is<atom_ptr>()) {
        return std::make_shared<expression>(any.as<atom_ptr>());
    } else {
        throw std::runtime_error("unexpected type to convert to expression");
    }
}

binary_op::op_type graph_compiler::get_binary_op(const std::string &op) {
    if (op == "+") {
        return binary_op::op_type::op_add;
    } else if (op == "-") {
        return binary_op::op_type::op_sub;
    } else if (op == "*") {
        return binary_op::op_type::op_multi;
    } else if (op == "/") {
        return binary_op::op_type::op_div;
    } else if (op == "&") {
        return binary_op::op_type::op_and;
    } else if (op == "|") {
        return binary_op::op_type::op_or;
    } else if (op == ">") {
        return binary_op::op_type::op_greater;
    } else if (op == ">=") {
        return binary_op::op_type::op_greater_or_equal;
    } else if (op == "<") {
        return binary_op::op_type::op_lower;
    } else if (op == "<=") {
        return binary_op::op_type::op_lower_or_equal;
    } else if (op == "^") {
        return binary_op::op_type::op_power;
    } else if (op == "=") {
        return binary_op::op_type::op_equal;
    } else if (op == "<>" || op == "!=") {
        return binary_op::op_type::op_not_equal;
    } else {
        throw std::runtime_error("unexpected binary binary_operator " + op);
    }
}

antlrcpp::Any graph_compiler::visitToUnary(HuskyLangParser::ToUnaryContext *context) {
    return wrap_expression(visit(context->unary()));
}

antlrcpp::Any graph_compiler::visitAddSubOp(HuskyLangParser::AddSubOpContext *context) {
    const expression_ptr &left_expr = wrap_expression(visit(context->plusOrMinus()));
    const expression_ptr &right_expr = wrap_expression(visit(context->multOrDiv()));
    binary_op::op_type opType = get_binary_op(context->op->getText());
    return binary_op(opType, left_expr, right_expr);
}

antlrcpp::Any graph_compiler::visitToMultOrDiv(HuskyLangParser::ToMultOrDivContext *context) {
    return visit(context->multOrDiv());
}

antlrcpp::Any graph_compiler::visitCompareOp(HuskyLangParser::CompareOpContext *context) {
    const expression_ptr &left_expr = wrap_expression(visit(context->compare()));
    const expression_ptr &right_expr = wrap_expression(visit(context->plusOrMinus()));
    binary_op::op_type opType = get_binary_op(context->op->getText());
    return binary_op(opType, left_expr, right_expr);
}

antlrcpp::Any graph_compiler::visitToPlusOrMinus(HuskyLangParser::ToPlusOrMinusContext *context) {
    return visit(context->plusOrMinus());
}

antlrcpp::Any graph_compiler::visitToCompare(HuskyLangParser::ToCompareContext *context) {
    return visit(context->compare());
}

antlrcpp::Any graph_compiler::visitLogicalOp(HuskyLangParser::LogicalOpContext *context) {
    const expression_ptr &left_expr = wrap_expression(visit(context->logical()));
    const expression_ptr &right_expr = wrap_expression(visit(context->compare()));
    binary_op::op_type opType = get_binary_op(context->op->getText());
    return binary_op(opType, left_expr, right_expr);
}

antlrcpp::Any graph_compiler::visitToLogical(HuskyLangParser::ToLogicalContext *context) {
    return visit(context->logical());
}

antlrcpp::Any graph_compiler::visitToExpression(HuskyLangParser::ToExpressionContext *context) {
    return wrap_expression(visit(context->expression()));
}

atom_ptr graph_compiler::wrap_atom(const Any &any) {
    if (any.is<atom_ptr>()) {
        return any.as<atom_ptr>();
    } else if (any.is<literal>()) {
        return std::make_shared<atom>(any.as<literal>());
    } else if (any.is<identifier_ref>()) {
        return std::make_shared<atom>(any.as<identifier_ref>());
    } else if (any.is<function_call>()) {
        return std::make_shared<atom>(any.as<function_call>());
    } else if (any.is<expression_ptr>()) {
        return std::make_shared<atom>(any.as<expression_ptr>());
    } else if (any.is<array_index>()) {
        return std::make_shared<atom>(any.as<array_index>());
    } else {
        throw std::runtime_error("unexpected child type");
    }
}

unary_op::op_type graph_compiler::get_unary_op(const std::string &op) {
    if (op == "-") {
        return unary_op::op_type::op_minus;
    } else if (op == "!") {
        return unary_op::op_type::op_not;
    } else {
        throw std::runtime_error("unexpected unary binary_operator " + op);
    }
}

graph graph_compiler::compile(const std::string &formula) {

    using namespace antlr4;
    using namespace antlr4::tree;
    using namespace antlrcpp;

    std::istringstream stream(formula);

    ANTLRInputStream input(stream);
    HuskyLangLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HuskyLangParser parser(&tokens);

    finalize on_final([&parser, &tokens, &lexer, &input]() {
        parser.reset();
        tokens.reset();
        lexer.reset();
        input.reset();
    });

    error_listener err_listener;
    parser.addErrorListener(&err_listener);

    ParseTree *tree = parser.statement();
    if (err_listener.has_error()) {
        throw err_listener.as_exception();
    }

    graph_compiler visitor;
    Any visited = visitor.visit(tree);

    return visited.as<expression_ptr>();
}

void graph_compiler::syntax_check(const std::string &formula, std::vector<syntax_error_item> &errors) {

    using namespace antlr4;
    using namespace antlr4::tree;
    using namespace antlrcpp;

    std::istringstream stream(formula);

    ANTLRInputStream input(stream);
    HuskyLangLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HuskyLangParser parser(&tokens);

    finalize on_final([&parser, &tokens, &lexer, &input]() {
        parser.reset();
        tokens.reset();
        lexer.reset();
        input.reset();
    });

    error_listener err_listener;
    parser.addErrorListener(&err_listener);

    parser.statement();
    if (err_listener.has_error()) {
        std::copy(err_listener.get_errors().begin(), err_listener.get_errors().end(),
                  std::back_inserter(errors));
    }
}
