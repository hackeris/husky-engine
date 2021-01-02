//
// Created by rainm on 2021/1/1.
//

#include <cmath>

#include "antlr4-runtime.h"
#include "grammar/HuskyLangLexer.h"
#include "grammar/HuskyLangParser.h"

#include "lang/Graph.h"
#include "GraphCompiler.h"

using namespace antlrcpp;

antlrcpp::Any GraphCompiler::visitInt(HuskyLangParser::IntContext *context) {
    auto value = (int) std::strtol(context->getText().c_str(), nullptr, 10);
    return Any(Literal{value});
}

antlrcpp::Any GraphCompiler::visitDouble(HuskyLangParser::DoubleContext *context) {
    auto value = (float) std::strtod(context->getText().c_str(), nullptr);
    return Any(Literal{value});
}

antlrcpp::Any GraphCompiler::visitConstantE(HuskyLangParser::ConstantEContext *context) {
    auto pi = (float) M_PI;
    return Any(Literal{pi});
}

antlrcpp::Any GraphCompiler::visitConstantPI(HuskyLangParser::ConstantPIContext *context) {
    auto pi = (float) M_E;
    return Any(Literal{pi});
}

antlrcpp::Any GraphCompiler::visitIdentifier(HuskyLangParser::IdentifierContext *context) {
    std::string identifierName = context->getText();
    return Any(IdentifierRef{std::move(identifierName)});
}

antlrcpp::Any GraphCompiler::visitToLiteral(HuskyLangParser::ToLiteralContext *context) {
    return visit(context->literal());
}

antlrcpp::Any GraphCompiler::visitToIdentifier(HuskyLangParser::ToIdentifierContext *context) {
    return visit(context->identifier());
}

antlrcpp::Any GraphCompiler::visitBraces(HuskyLangParser::BracesContext *context) {
    return visit(context->expression());
}

antlrcpp::Any GraphCompiler::visitArrayIndex(HuskyLangParser::ArrayIndexContext *context) {
    const Any &ident = visit(context->identifier());
    const Any &idx = visit(context->expression());
    return Any(ArrayIndex(ident.as<IdentifierRef>(),
                          idx.as<ExpressionPtr>()));
}

antlrcpp::Any GraphCompiler::visitArgList(HuskyLangParser::ArgListContext *context) {

    Any parsedArgs;
    if (context->argList() == nullptr) {
        parsedArgs = std::make_shared<std::vector<ExpressionPtr>>();
    } else {
        parsedArgs = visit(context->argList());
    }

    const ArgList &parsed = parsedArgs.as<ArgList>();

    const Any &expr = toExpression(visit(context->expression()));
    parsed->push_back(expr.as<ExpressionPtr>());
    return parsed;
}

antlrcpp::Any GraphCompiler::visitFuncCall(HuskyLangParser::FuncCallContext *context) {

    const Any &args = visit(context->argList());
    std::string funcName = context->identifier()->getText();

    return FunctionCall(std::move(funcName), args.as<ArgList>());
}

antlrcpp::Any GraphCompiler::visitPower(HuskyLangParser::PowerContext *context) {

    const Any &left = visit(context->powr());
    const Any &right = visit(context->atom());

    const std::shared_ptr<Atom> &rightAtom = toAtom(right);

    if (left.is<AtomPtr>()) {
        const std::shared_ptr<Atom> &leftAtom = left.as<AtomPtr>();
        return BinaryOp(BinaryOp::Type::Power,
                        std::make_shared<Expression>(leftAtom),
                        std::make_shared<Expression>(rightAtom));
    } else if (left.is<BinaryOp>()) {
        const auto &leftPower = left.as<BinaryOp>();
        return BinaryOp(BinaryOp::Type::Power,
                        std::make_shared<Expression>(leftPower),
                        std::make_shared<Expression>(rightAtom));
    } else {
        throw std::runtime_error("unexpected left type");
    }
}

antlrcpp::Any GraphCompiler::visitToAtom(HuskyLangParser::ToAtomContext *context) {
    const Any &atomValue = visit(context->atom());
    return toAtom(atomValue);
}

antlrcpp::Any GraphCompiler::visitToPower(HuskyLangParser::ToPowerContext *context) {
    return visit(context->powr());
}

antlrcpp::Any GraphCompiler::visitUnaryOp(HuskyLangParser::UnaryOpContext *context) {
    const std::string &opText = context->op->getText();
    UnaryOp::Type opType = getUnaryOp(opText);

    const Any &operand = visit(context->powr());
    if (operand.is<BinaryOp>()) {
        return UnaryOp(opType, operand.as<BinaryOp>());
    } else if (operand.is<AtomPtr>()) {
        return UnaryOp(opType, operand.as<AtomPtr>());
    } else {
        throw std::runtime_error("unexpected operand type");
    }
}

antlrcpp::Any GraphCompiler::visitMultiDivOp(HuskyLangParser::MultiDivOpContext *context) {
    const ExpressionPtr &leftExpr = toExpression(visit(context->multOrDiv()));
    const ExpressionPtr &rightExpr = toExpression(visit(context->powr()));
    BinaryOp::Type opType = getBinaryOp(context->op->getText());
    return BinaryOp(opType, leftExpr, rightExpr);
}

ExpressionPtr GraphCompiler::toExpression(const Any &any) {
    if (any.is<ExpressionPtr>()) {
        return any;
    } else if (any.is<BinaryOp>()) {
        return std::make_shared<Expression>(any.as<BinaryOp>());
    } else if (any.is<UnaryOp>()) {
        return std::make_shared<Expression>(any.as<UnaryOp>());
    } else if (any.is<AtomPtr>()) {
        return std::make_shared<Expression>(any.as<AtomPtr>());
    } else {
        throw std::runtime_error("unexpected type to convert to expression");
    }
}

BinaryOp::Type GraphCompiler::getBinaryOp(const std::string &opText) {
    if (opText == "+") {
        return BinaryOp::Type::Add;
    } else if (opText == "-") {
        return BinaryOp::Type::Sub;
    } else if (opText == "*") {
        return BinaryOp::Type::Multi;
    } else if (opText == "/") {
        return BinaryOp::Type::Div;
    } else if (opText == "&") {
        return BinaryOp::Type::And;
    } else if (opText == "|") {
        return BinaryOp::Type::Or;
    } else if (opText == ">") {
        return BinaryOp::Type::Greater;
    } else if (opText == ">=") {
        return BinaryOp::Type::GreaterOrEqual;
    } else if (opText == "<") {
        return BinaryOp::Type::Lower;
    } else if (opText == "<=") {
        return BinaryOp::Type::LowerOrEqual;
    } else if (opText == "^") {
        return BinaryOp::Type::Power;
    } else if (opText == "=") {
        return BinaryOp::Type::Equal;
    } else if (opText == "<>" || opText == "!=") {
        return BinaryOp::Type::NotEqual;
    } else {
        throw std::runtime_error("unexpected binary binaryOperator " + opText);
    }
}

antlrcpp::Any GraphCompiler::visitToUnary(HuskyLangParser::ToUnaryContext *context) {
    return toExpression(visit(context->unary()));
}

antlrcpp::Any GraphCompiler::visitAddSubOp(HuskyLangParser::AddSubOpContext *context) {
    const ExpressionPtr &leftExpr = toExpression(visit(context->plusOrMinus()));
    const ExpressionPtr &rightExpr = toExpression(visit(context->multOrDiv()));
    BinaryOp::Type opType = getBinaryOp(context->op->getText());
    return BinaryOp(opType, leftExpr, rightExpr);
}

antlrcpp::Any GraphCompiler::visitToMultOrDiv(HuskyLangParser::ToMultOrDivContext *context) {
    return visit(context->multOrDiv());
}

antlrcpp::Any GraphCompiler::visitCompareOp(HuskyLangParser::CompareOpContext *context) {
    const ExpressionPtr &leftExpr = toExpression(visit(context->compare()));
    const ExpressionPtr &rightExpr = toExpression(visit(context->plusOrMinus()));
    BinaryOp::Type opType = getBinaryOp(context->op->getText());
    return BinaryOp(opType, leftExpr, rightExpr);
}

antlrcpp::Any GraphCompiler::visitToPlusOrMinus(HuskyLangParser::ToPlusOrMinusContext *context) {
    return visit(context->plusOrMinus());
}

antlrcpp::Any GraphCompiler::visitToCompare(HuskyLangParser::ToCompareContext *context) {
    return visit(context->compare());
}

antlrcpp::Any GraphCompiler::visitLogicalOp(HuskyLangParser::LogicalOpContext *context) {
    const ExpressionPtr &leftExpr = toExpression(visit(context->logical()));
    const ExpressionPtr &rightExpr = toExpression(visit(context->compare()));
    BinaryOp::Type opType = getBinaryOp(context->op->getText());
    return BinaryOp(opType, leftExpr, rightExpr);
}

antlrcpp::Any GraphCompiler::visitToLogical(HuskyLangParser::ToLogicalContext *context) {
    return visit(context->logical());
}

antlrcpp::Any GraphCompiler::visitToExpression(HuskyLangParser::ToExpressionContext *context) {
    return toExpression(visit(context->expression()));
}

AtomPtr GraphCompiler::toAtom(const Any &any) {
    if (any.is<AtomPtr>()) {
        return any.as<AtomPtr>();
    } else if (any.is<Literal>()) {
        return std::make_shared<Atom>(any.as<Literal>());
    } else if (any.is<IdentifierRef>()) {
        return std::make_shared<Atom>(any.as<IdentifierRef>());
    } else if (any.is<FunctionCall>()) {
        return std::make_shared<Atom>(any.as<FunctionCall>());
    } else if (any.is<ExpressionPtr>()) {
        return std::make_shared<Atom>(any.as<ExpressionPtr>());
    } else if (any.is<ArrayIndex>()) {
        return std::make_shared<Atom>(any.as<ArrayIndex>());
    } else {
        throw std::runtime_error("unexpected child type");
    }
}

UnaryOp::Type GraphCompiler::getUnaryOp(const std::string &opText) {
    if (opText == "-") {
        return UnaryOp::Type::Minus;
    } else if (opText == "!") {
        return UnaryOp::Type::Not;
    } else {
        throw std::runtime_error("unexpected unary binaryOperator " + opText);
    }
}

ExpressionPtr GraphCompiler::compile(const std::string &formula) {

    using namespace antlr4;
    using namespace antlrcpp;

    std::istringstream stream(formula);

    ANTLRInputStream input(stream);
    HuskyLangLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HuskyLangParser parser(&tokens);

    tree::ParseTree *tree = parser.statement();
    GraphCompiler visitor;

    Any visited = visitor.visit(tree);
    return visited.as<ExpressionPtr>();
}
