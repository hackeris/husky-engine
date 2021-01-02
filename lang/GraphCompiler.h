//
// Created by rainm on 2021/1/1.
//

#ifndef HUSKY_COMPUTE_GRAPHCOMPILER_H
#define HUSKY_COMPUTE_GRAPHCOMPILER_H

#include "lang/Graph.h"
#include "grammar/HuskyLangVisitor.h"

class GraphCompiler : public HuskyLangVisitor {

public:
    antlrcpp::Any visitToExpression(HuskyLangParser::ToExpressionContext *context) override;

    antlrcpp::Any visitToLogical(HuskyLangParser::ToLogicalContext *context) override;

    antlrcpp::Any visitLogicalOp(HuskyLangParser::LogicalOpContext *context) override;

    antlrcpp::Any visitToCompare(HuskyLangParser::ToCompareContext *context) override;

    antlrcpp::Any visitToPlusOrMinus(HuskyLangParser::ToPlusOrMinusContext *context) override;

    antlrcpp::Any visitCompareOp(HuskyLangParser::CompareOpContext *context) override;

    antlrcpp::Any visitToMultOrDiv(HuskyLangParser::ToMultOrDivContext *context) override;

    antlrcpp::Any visitAddSubOp(HuskyLangParser::AddSubOpContext *context) override;

    antlrcpp::Any visitToUnary(HuskyLangParser::ToUnaryContext *context) override;

    antlrcpp::Any visitMultiDivOp(HuskyLangParser::MultiDivOpContext *context) override;

    antlrcpp::Any visitUnaryOp(HuskyLangParser::UnaryOpContext *context) override;

    antlrcpp::Any visitToPower(HuskyLangParser::ToPowerContext *context) override;

    antlrcpp::Any visitToAtom(HuskyLangParser::ToAtomContext *context) override;

    antlrcpp::Any visitPower(HuskyLangParser::PowerContext *context) override;

    antlrcpp::Any visitToLiteral(HuskyLangParser::ToLiteralContext *context) override;

    antlrcpp::Any visitToIdentifier(HuskyLangParser::ToIdentifierContext *context) override;

    antlrcpp::Any visitFuncCall(HuskyLangParser::FuncCallContext *context) override;

    antlrcpp::Any visitBraces(HuskyLangParser::BracesContext *context) override;

    antlrcpp::Any visitArrayIndex(HuskyLangParser::ArrayIndexContext *context) override;

    antlrcpp::Any visitArgList(HuskyLangParser::ArgListContext *context) override;

    antlrcpp::Any visitIdentifier(HuskyLangParser::IdentifierContext *context) override;

    antlrcpp::Any visitConstantPI(HuskyLangParser::ConstantPIContext *context) override;

    antlrcpp::Any visitConstantE(HuskyLangParser::ConstantEContext *context) override;

    antlrcpp::Any visitDouble(HuskyLangParser::DoubleContext *context) override;

    antlrcpp::Any visitInt(HuskyLangParser::IntContext *context) override;

    static ExpressionPtr compile(const std::string &formula);

private:
    static ExpressionPtr toExpression(const antlrcpp::Any &any);

    static AtomPtr toAtom(const antlrcpp::Any &any);

    static BinaryOp::Type getBinaryOp(const std::string &opText);

    static UnaryOp::Type getUnaryOp(const std::string &opText);
};


#endif //HUSKY_COMPUTE_GRAPHCOMPILER_H
