
// Generated from grammar/HuskyLang.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "HuskyLangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by HuskyLangParser.
 */
class  HuskyLangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HuskyLangParser.
   */
    virtual antlrcpp::Any visitToExpression(HuskyLangParser::ToExpressionContext *context) = 0;

    virtual antlrcpp::Any visitToLogical(HuskyLangParser::ToLogicalContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOp(HuskyLangParser::LogicalOpContext *context) = 0;

    virtual antlrcpp::Any visitToCompare(HuskyLangParser::ToCompareContext *context) = 0;

    virtual antlrcpp::Any visitToPlusOrMinus(HuskyLangParser::ToPlusOrMinusContext *context) = 0;

    virtual antlrcpp::Any visitCompareOp(HuskyLangParser::CompareOpContext *context) = 0;

    virtual antlrcpp::Any visitToMultOrDiv(HuskyLangParser::ToMultOrDivContext *context) = 0;

    virtual antlrcpp::Any visitAddSubOp(HuskyLangParser::AddSubOpContext *context) = 0;

    virtual antlrcpp::Any visitToUnary(HuskyLangParser::ToUnaryContext *context) = 0;

    virtual antlrcpp::Any visitMultiDivOp(HuskyLangParser::MultiDivOpContext *context) = 0;

    virtual antlrcpp::Any visitUnaryOp(HuskyLangParser::UnaryOpContext *context) = 0;

    virtual antlrcpp::Any visitToPower(HuskyLangParser::ToPowerContext *context) = 0;

    virtual antlrcpp::Any visitToAtom(HuskyLangParser::ToAtomContext *context) = 0;

    virtual antlrcpp::Any visitPower(HuskyLangParser::PowerContext *context) = 0;

    virtual antlrcpp::Any visitToLiteral(HuskyLangParser::ToLiteralContext *context) = 0;

    virtual antlrcpp::Any visitToIdentifier(HuskyLangParser::ToIdentifierContext *context) = 0;

    virtual antlrcpp::Any visitFuncCall(HuskyLangParser::FuncCallContext *context) = 0;

    virtual antlrcpp::Any visitBraces(HuskyLangParser::BracesContext *context) = 0;

    virtual antlrcpp::Any visitArrayIndex(HuskyLangParser::ArrayIndexContext *context) = 0;

    virtual antlrcpp::Any visitArgList(HuskyLangParser::ArgListContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(HuskyLangParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitConstantPI(HuskyLangParser::ConstantPIContext *context) = 0;

    virtual antlrcpp::Any visitConstantE(HuskyLangParser::ConstantEContext *context) = 0;

    virtual antlrcpp::Any visitDouble(HuskyLangParser::DoubleContext *context) = 0;

    virtual antlrcpp::Any visitInt(HuskyLangParser::IntContext *context) = 0;


};

