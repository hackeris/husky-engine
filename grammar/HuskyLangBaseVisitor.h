
// Generated from grammar/HuskyLang.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "HuskyLangVisitor.h"


/**
 * This class provides an empty implementation of HuskyLangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HuskyLangBaseVisitor : public HuskyLangVisitor {
public:

  virtual antlrcpp::Any visitToExpression(HuskyLangParser::ToExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToLogical(HuskyLangParser::ToLogicalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicalOp(HuskyLangParser::LogicalOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToCompare(HuskyLangParser::ToCompareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToPlusOrMinus(HuskyLangParser::ToPlusOrMinusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareOp(HuskyLangParser::CompareOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToMultOrDiv(HuskyLangParser::ToMultOrDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddSubOp(HuskyLangParser::AddSubOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToUnary(HuskyLangParser::ToUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultiDivOp(HuskyLangParser::MultiDivOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryOp(HuskyLangParser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToPower(HuskyLangParser::ToPowerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToAtom(HuskyLangParser::ToAtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPower(HuskyLangParser::PowerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToLiteral(HuskyLangParser::ToLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitToIdentifier(HuskyLangParser::ToIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncCall(HuskyLangParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBraces(HuskyLangParser::BracesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayIndex(HuskyLangParser::ArrayIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArgList(HuskyLangParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(HuskyLangParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantPI(HuskyLangParser::ConstantPIContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantE(HuskyLangParser::ConstantEContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDouble(HuskyLangParser::DoubleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInt(HuskyLangParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }


};

