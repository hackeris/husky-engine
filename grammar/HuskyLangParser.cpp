
// Generated from grammar/HuskyLang.g4 by ANTLR 4.8


#include "HuskyLangVisitor.h"

#include "HuskyLangParser.h"


using namespace antlrcpp;
using namespace antlr4;

HuskyLangParser::HuskyLangParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

HuskyLangParser::~HuskyLangParser() {
  delete _interpreter;
}

std::string HuskyLangParser::getGrammarFileName() const {
  return "HuskyLang.g4";
}

const std::vector<std::string>& HuskyLangParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& HuskyLangParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StatementContext ------------------------------------------------------------------

HuskyLangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::StatementContext::getRuleIndex() const {
  return HuskyLangParser::RuleStatement;
}

void HuskyLangParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToExpressionContext ------------------------------------------------------------------

HuskyLangParser::ExpressionContext* HuskyLangParser::ToExpressionContext::expression() {
  return getRuleContext<HuskyLangParser::ExpressionContext>(0);
}

HuskyLangParser::ToExpressionContext::ToExpressionContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToExpression(this);
  else
    return visitor->visitChildren(this);
}
HuskyLangParser::StatementContext* HuskyLangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 0, HuskyLangParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<HuskyLangParser::ToExpressionContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(24);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

HuskyLangParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::ExpressionContext::getRuleIndex() const {
  return HuskyLangParser::RuleExpression;
}

void HuskyLangParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToLogicalContext ------------------------------------------------------------------

HuskyLangParser::LogicalContext* HuskyLangParser::ToLogicalContext::logical() {
  return getRuleContext<HuskyLangParser::LogicalContext>(0);
}

HuskyLangParser::ToLogicalContext::ToLogicalContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToLogicalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToLogical(this);
  else
    return visitor->visitChildren(this);
}
HuskyLangParser::ExpressionContext* HuskyLangParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, HuskyLangParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<ExpressionContext *>(_tracker.createInstance<HuskyLangParser::ToLogicalContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(26);
    logical(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalContext ------------------------------------------------------------------

HuskyLangParser::LogicalContext::LogicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::LogicalContext::getRuleIndex() const {
  return HuskyLangParser::RuleLogical;
}

void HuskyLangParser::LogicalContext::copyFrom(LogicalContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LogicalOpContext ------------------------------------------------------------------

HuskyLangParser::LogicalContext* HuskyLangParser::LogicalOpContext::logical() {
  return getRuleContext<HuskyLangParser::LogicalContext>(0);
}

HuskyLangParser::CompareContext* HuskyLangParser::LogicalOpContext::compare() {
  return getRuleContext<HuskyLangParser::CompareContext>(0);
}

tree::TerminalNode* HuskyLangParser::LogicalOpContext::AND() {
  return getToken(HuskyLangParser::AND, 0);
}

tree::TerminalNode* HuskyLangParser::LogicalOpContext::OR() {
  return getToken(HuskyLangParser::OR, 0);
}

HuskyLangParser::LogicalOpContext::LogicalOpContext(LogicalContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::LogicalOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitLogicalOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToCompareContext ------------------------------------------------------------------

HuskyLangParser::CompareContext* HuskyLangParser::ToCompareContext::compare() {
  return getRuleContext<HuskyLangParser::CompareContext>(0);
}

HuskyLangParser::ToCompareContext::ToCompareContext(LogicalContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToCompareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToCompare(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::LogicalContext* HuskyLangParser::logical() {
   return logical(0);
}

HuskyLangParser::LogicalContext* HuskyLangParser::logical(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::LogicalContext *_localctx = _tracker.createInstance<LogicalContext>(_ctx, parentState);
  HuskyLangParser::LogicalContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, HuskyLangParser::RuleLogical, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToCompareContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(29);
    compare(0);
    _ctx->stop = _input->LT(-1);
    setState(39);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(37);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<LogicalOpContext>(_tracker.createInstance<LogicalContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleLogical);
          setState(31);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(32);
          dynamic_cast<LogicalOpContext *>(_localctx)->op = match(HuskyLangParser::AND);
          setState(33);
          compare(0);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<LogicalOpContext>(_tracker.createInstance<LogicalContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleLogical);
          setState(34);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(35);
          dynamic_cast<LogicalOpContext *>(_localctx)->op = match(HuskyLangParser::OR);
          setState(36);
          compare(0);
          break;
        }

        } 
      }
      setState(41);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- CompareContext ------------------------------------------------------------------

HuskyLangParser::CompareContext::CompareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::CompareContext::getRuleIndex() const {
  return HuskyLangParser::RuleCompare;
}

void HuskyLangParser::CompareContext::copyFrom(CompareContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToPlusOrMinusContext ------------------------------------------------------------------

HuskyLangParser::PlusOrMinusContext* HuskyLangParser::ToPlusOrMinusContext::plusOrMinus() {
  return getRuleContext<HuskyLangParser::PlusOrMinusContext>(0);
}

HuskyLangParser::ToPlusOrMinusContext::ToPlusOrMinusContext(CompareContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToPlusOrMinusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToPlusOrMinus(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CompareOpContext ------------------------------------------------------------------

HuskyLangParser::CompareContext* HuskyLangParser::CompareOpContext::compare() {
  return getRuleContext<HuskyLangParser::CompareContext>(0);
}

HuskyLangParser::PlusOrMinusContext* HuskyLangParser::CompareOpContext::plusOrMinus() {
  return getRuleContext<HuskyLangParser::PlusOrMinusContext>(0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::EQUAL() {
  return getToken(HuskyLangParser::EQUAL, 0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::NEQ() {
  return getToken(HuskyLangParser::NEQ, 0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::GT() {
  return getToken(HuskyLangParser::GT, 0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::GTE() {
  return getToken(HuskyLangParser::GTE, 0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::LT() {
  return getToken(HuskyLangParser::LT, 0);
}

tree::TerminalNode* HuskyLangParser::CompareOpContext::LTE() {
  return getToken(HuskyLangParser::LTE, 0);
}

HuskyLangParser::CompareOpContext::CompareOpContext(CompareContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::CompareOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitCompareOp(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::CompareContext* HuskyLangParser::compare() {
   return compare(0);
}

HuskyLangParser::CompareContext* HuskyLangParser::compare(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::CompareContext *_localctx = _tracker.createInstance<CompareContext>(_ctx, parentState);
  HuskyLangParser::CompareContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, HuskyLangParser::RuleCompare, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToPlusOrMinusContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(43);
    plusOrMinus(0);
    _ctx->stop = _input->LT(-1);
    setState(65);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(63);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(45);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(46);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::EQUAL);
          setState(47);
          plusOrMinus(0);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(48);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(49);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::NEQ);
          setState(50);
          plusOrMinus(0);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(51);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(52);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::GT);
          setState(53);
          plusOrMinus(0);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(54);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(55);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::GTE);
          setState(56);
          plusOrMinus(0);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(57);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(58);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::LT);
          setState(59);
          plusOrMinus(0);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<CompareOpContext>(_tracker.createInstance<CompareContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCompare);
          setState(60);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(61);
          dynamic_cast<CompareOpContext *>(_localctx)->op = match(HuskyLangParser::LTE);
          setState(62);
          plusOrMinus(0);
          break;
        }

        } 
      }
      setState(67);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PlusOrMinusContext ------------------------------------------------------------------

HuskyLangParser::PlusOrMinusContext::PlusOrMinusContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::PlusOrMinusContext::getRuleIndex() const {
  return HuskyLangParser::RulePlusOrMinus;
}

void HuskyLangParser::PlusOrMinusContext::copyFrom(PlusOrMinusContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToMultOrDivContext ------------------------------------------------------------------

HuskyLangParser::MultOrDivContext* HuskyLangParser::ToMultOrDivContext::multOrDiv() {
  return getRuleContext<HuskyLangParser::MultOrDivContext>(0);
}

HuskyLangParser::ToMultOrDivContext::ToMultOrDivContext(PlusOrMinusContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToMultOrDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToMultOrDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubOpContext ------------------------------------------------------------------

HuskyLangParser::PlusOrMinusContext* HuskyLangParser::AddSubOpContext::plusOrMinus() {
  return getRuleContext<HuskyLangParser::PlusOrMinusContext>(0);
}

HuskyLangParser::MultOrDivContext* HuskyLangParser::AddSubOpContext::multOrDiv() {
  return getRuleContext<HuskyLangParser::MultOrDivContext>(0);
}

tree::TerminalNode* HuskyLangParser::AddSubOpContext::PLUS() {
  return getToken(HuskyLangParser::PLUS, 0);
}

tree::TerminalNode* HuskyLangParser::AddSubOpContext::MINUS() {
  return getToken(HuskyLangParser::MINUS, 0);
}

HuskyLangParser::AddSubOpContext::AddSubOpContext(PlusOrMinusContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::AddSubOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitAddSubOp(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::PlusOrMinusContext* HuskyLangParser::plusOrMinus() {
   return plusOrMinus(0);
}

HuskyLangParser::PlusOrMinusContext* HuskyLangParser::plusOrMinus(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::PlusOrMinusContext *_localctx = _tracker.createInstance<PlusOrMinusContext>(_ctx, parentState);
  HuskyLangParser::PlusOrMinusContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, HuskyLangParser::RulePlusOrMinus, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToMultOrDivContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(69);
    multOrDiv(0);
    _ctx->stop = _input->LT(-1);
    setState(79);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(77);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AddSubOpContext>(_tracker.createInstance<PlusOrMinusContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RulePlusOrMinus);
          setState(71);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(72);
          dynamic_cast<AddSubOpContext *>(_localctx)->op = match(HuskyLangParser::PLUS);
          setState(73);
          multOrDiv(0);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubOpContext>(_tracker.createInstance<PlusOrMinusContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RulePlusOrMinus);
          setState(74);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(75);
          dynamic_cast<AddSubOpContext *>(_localctx)->op = match(HuskyLangParser::MINUS);
          setState(76);
          multOrDiv(0);
          break;
        }

        } 
      }
      setState(81);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MultOrDivContext ------------------------------------------------------------------

HuskyLangParser::MultOrDivContext::MultOrDivContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::MultOrDivContext::getRuleIndex() const {
  return HuskyLangParser::RuleMultOrDiv;
}

void HuskyLangParser::MultOrDivContext::copyFrom(MultOrDivContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToUnaryContext ------------------------------------------------------------------

HuskyLangParser::UnaryContext* HuskyLangParser::ToUnaryContext::unary() {
  return getRuleContext<HuskyLangParser::UnaryContext>(0);
}

HuskyLangParser::ToUnaryContext::ToUnaryContext(MultOrDivContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiDivOpContext ------------------------------------------------------------------

HuskyLangParser::MultOrDivContext* HuskyLangParser::MultiDivOpContext::multOrDiv() {
  return getRuleContext<HuskyLangParser::MultOrDivContext>(0);
}

HuskyLangParser::PowrContext* HuskyLangParser::MultiDivOpContext::powr() {
  return getRuleContext<HuskyLangParser::PowrContext>(0);
}

tree::TerminalNode* HuskyLangParser::MultiDivOpContext::MULT() {
  return getToken(HuskyLangParser::MULT, 0);
}

tree::TerminalNode* HuskyLangParser::MultiDivOpContext::DIV() {
  return getToken(HuskyLangParser::DIV, 0);
}

HuskyLangParser::MultiDivOpContext::MultiDivOpContext(MultOrDivContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::MultiDivOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitMultiDivOp(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::MultOrDivContext* HuskyLangParser::multOrDiv() {
   return multOrDiv(0);
}

HuskyLangParser::MultOrDivContext* HuskyLangParser::multOrDiv(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::MultOrDivContext *_localctx = _tracker.createInstance<MultOrDivContext>(_ctx, parentState);
  HuskyLangParser::MultOrDivContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, HuskyLangParser::RuleMultOrDiv, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToUnaryContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(83);
    unary();
    _ctx->stop = _input->LT(-1);
    setState(93);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(91);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MultiDivOpContext>(_tracker.createInstance<MultOrDivContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleMultOrDiv);
          setState(85);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(86);
          dynamic_cast<MultiDivOpContext *>(_localctx)->op = match(HuskyLangParser::MULT);
          setState(87);
          powr(0);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MultiDivOpContext>(_tracker.createInstance<MultOrDivContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleMultOrDiv);
          setState(88);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(89);
          dynamic_cast<MultiDivOpContext *>(_localctx)->op = match(HuskyLangParser::DIV);
          setState(90);
          powr(0);
          break;
        }

        } 
      }
      setState(95);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryContext ------------------------------------------------------------------

HuskyLangParser::UnaryContext::UnaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::UnaryContext::getRuleIndex() const {
  return HuskyLangParser::RuleUnary;
}

void HuskyLangParser::UnaryContext::copyFrom(UnaryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryOpContext ------------------------------------------------------------------

HuskyLangParser::PowrContext* HuskyLangParser::UnaryOpContext::powr() {
  return getRuleContext<HuskyLangParser::PowrContext>(0);
}

tree::TerminalNode* HuskyLangParser::UnaryOpContext::MINUS() {
  return getToken(HuskyLangParser::MINUS, 0);
}

tree::TerminalNode* HuskyLangParser::UnaryOpContext::NOT() {
  return getToken(HuskyLangParser::NOT, 0);
}

HuskyLangParser::UnaryOpContext::UnaryOpContext(UnaryContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToPowerContext ------------------------------------------------------------------

HuskyLangParser::PowrContext* HuskyLangParser::ToPowerContext::powr() {
  return getRuleContext<HuskyLangParser::PowrContext>(0);
}

HuskyLangParser::ToPowerContext::ToPowerContext(UnaryContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToPowerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToPower(this);
  else
    return visitor->visitChildren(this);
}
HuskyLangParser::UnaryContext* HuskyLangParser::unary() {
  UnaryContext *_localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
  enterRule(_localctx, 12, HuskyLangParser::RuleUnary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(101);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HuskyLangParser::MINUS: {
        _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<HuskyLangParser::UnaryOpContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(96);
        dynamic_cast<UnaryOpContext *>(_localctx)->op = match(HuskyLangParser::MINUS);
        setState(97);
        powr(0);
        break;
      }

      case HuskyLangParser::NOT: {
        _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<HuskyLangParser::UnaryOpContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(98);
        dynamic_cast<UnaryOpContext *>(_localctx)->op = match(HuskyLangParser::NOT);
        setState(99);
        powr(0);
        break;
      }

      case HuskyLangParser::INT:
      case HuskyLangParser::DOUBLE:
      case HuskyLangParser::PI:
      case HuskyLangParser::E:
      case HuskyLangParser::ID:
      case HuskyLangParser::LPAR: {
        _localctx = dynamic_cast<UnaryContext *>(_tracker.createInstance<HuskyLangParser::ToPowerContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(100);
        powr(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PowrContext ------------------------------------------------------------------

HuskyLangParser::PowrContext::PowrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::PowrContext::getRuleIndex() const {
  return HuskyLangParser::RulePowr;
}

void HuskyLangParser::PowrContext::copyFrom(PowrContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToAtomContext ------------------------------------------------------------------

HuskyLangParser::AtomContext* HuskyLangParser::ToAtomContext::atom() {
  return getRuleContext<HuskyLangParser::AtomContext>(0);
}

HuskyLangParser::ToAtomContext::ToAtomContext(PowrContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToAtom(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PowerContext ------------------------------------------------------------------

HuskyLangParser::PowrContext* HuskyLangParser::PowerContext::powr() {
  return getRuleContext<HuskyLangParser::PowrContext>(0);
}

HuskyLangParser::AtomContext* HuskyLangParser::PowerContext::atom() {
  return getRuleContext<HuskyLangParser::AtomContext>(0);
}

tree::TerminalNode* HuskyLangParser::PowerContext::POW() {
  return getToken(HuskyLangParser::POW, 0);
}

HuskyLangParser::PowerContext::PowerContext(PowrContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::PowerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitPower(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::PowrContext* HuskyLangParser::powr() {
   return powr(0);
}

HuskyLangParser::PowrContext* HuskyLangParser::powr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::PowrContext *_localctx = _tracker.createInstance<PowrContext>(_ctx, parentState);
  HuskyLangParser::PowrContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, HuskyLangParser::RulePowr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToAtomContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(104);
    atom();
    _ctx->stop = _input->LT(-1);
    setState(111);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<PowerContext>(_tracker.createInstance<PowrContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RulePowr);
        setState(106);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(107);
        dynamic_cast<PowerContext *>(_localctx)->op = match(HuskyLangParser::POW);
        setState(108);
        atom(); 
      }
      setState(113);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

HuskyLangParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::AtomContext::getRuleIndex() const {
  return HuskyLangParser::RuleAtom;
}

void HuskyLangParser::AtomContext::copyFrom(AtomContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncCallContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::FuncCallContext::LPAR() {
  return getToken(HuskyLangParser::LPAR, 0);
}

tree::TerminalNode* HuskyLangParser::FuncCallContext::RPAR() {
  return getToken(HuskyLangParser::RPAR, 0);
}

HuskyLangParser::IdentifierContext* HuskyLangParser::FuncCallContext::identifier() {
  return getRuleContext<HuskyLangParser::IdentifierContext>(0);
}

HuskyLangParser::ArgListContext* HuskyLangParser::FuncCallContext::argList() {
  return getRuleContext<HuskyLangParser::ArgListContext>(0);
}

HuskyLangParser::FuncCallContext::FuncCallContext(AtomContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BracesContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::BracesContext::LPAR() {
  return getToken(HuskyLangParser::LPAR, 0);
}

HuskyLangParser::ExpressionContext* HuskyLangParser::BracesContext::expression() {
  return getRuleContext<HuskyLangParser::ExpressionContext>(0);
}

tree::TerminalNode* HuskyLangParser::BracesContext::RPAR() {
  return getToken(HuskyLangParser::RPAR, 0);
}

HuskyLangParser::BracesContext::BracesContext(AtomContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::BracesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitBraces(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToIdentifierContext ------------------------------------------------------------------

HuskyLangParser::IdentifierContext* HuskyLangParser::ToIdentifierContext::identifier() {
  return getRuleContext<HuskyLangParser::IdentifierContext>(0);
}

HuskyLangParser::ToIdentifierContext::ToIdentifierContext(AtomContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToLiteralContext ------------------------------------------------------------------

HuskyLangParser::LiteralContext* HuskyLangParser::ToLiteralContext::literal() {
  return getRuleContext<HuskyLangParser::LiteralContext>(0);
}

HuskyLangParser::ToLiteralContext::ToLiteralContext(AtomContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ToLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitToLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayIndexContext ------------------------------------------------------------------

HuskyLangParser::IdentifierContext* HuskyLangParser::ArrayIndexContext::identifier() {
  return getRuleContext<HuskyLangParser::IdentifierContext>(0);
}

HuskyLangParser::ExpressionContext* HuskyLangParser::ArrayIndexContext::expression() {
  return getRuleContext<HuskyLangParser::ExpressionContext>(0);
}

HuskyLangParser::ArrayIndexContext::ArrayIndexContext(AtomContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ArrayIndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitArrayIndex(this);
  else
    return visitor->visitChildren(this);
}
HuskyLangParser::AtomContext* HuskyLangParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 16, HuskyLangParser::RuleAtom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(132);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<HuskyLangParser::ToLiteralContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(114);
      literal();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<HuskyLangParser::ToIdentifierContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(115);
      identifier();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<HuskyLangParser::FuncCallContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(116);
      dynamic_cast<FuncCallContext *>(_localctx)->functionName = identifier();
      setState(117);
      match(HuskyLangParser::LPAR);
      setState(119);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << HuskyLangParser::INT)
        | (1ULL << HuskyLangParser::DOUBLE)
        | (1ULL << HuskyLangParser::PI)
        | (1ULL << HuskyLangParser::E)
        | (1ULL << HuskyLangParser::ID)
        | (1ULL << HuskyLangParser::MINUS)
        | (1ULL << HuskyLangParser::NOT)
        | (1ULL << HuskyLangParser::LPAR))) != 0)) {
        setState(118);
        argList(0);
      }
      setState(121);
      match(HuskyLangParser::RPAR);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<HuskyLangParser::BracesContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(123);
      match(HuskyLangParser::LPAR);
      setState(124);
      expression();
      setState(125);
      match(HuskyLangParser::RPAR);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<AtomContext *>(_tracker.createInstance<HuskyLangParser::ArrayIndexContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(127);
      dynamic_cast<ArrayIndexContext *>(_localctx)->indexable = identifier();
      setState(128);
      match(HuskyLangParser::T__0);
      setState(129);
      dynamic_cast<ArrayIndexContext *>(_localctx)->index = expression();
      setState(130);
      match(HuskyLangParser::T__1);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

HuskyLangParser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HuskyLangParser::ExpressionContext* HuskyLangParser::ArgListContext::expression() {
  return getRuleContext<HuskyLangParser::ExpressionContext>(0);
}

HuskyLangParser::ArgListContext* HuskyLangParser::ArgListContext::argList() {
  return getRuleContext<HuskyLangParser::ArgListContext>(0);
}


size_t HuskyLangParser::ArgListContext::getRuleIndex() const {
  return HuskyLangParser::RuleArgList;
}


antlrcpp::Any HuskyLangParser::ArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitArgList(this);
  else
    return visitor->visitChildren(this);
}


HuskyLangParser::ArgListContext* HuskyLangParser::argList() {
   return argList(0);
}

HuskyLangParser::ArgListContext* HuskyLangParser::argList(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HuskyLangParser::ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, parentState);
  HuskyLangParser::ArgListContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, HuskyLangParser::RuleArgList, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(135);
    expression();
    _ctx->stop = _input->LT(-1);
    setState(142);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ArgListContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleArgList);
        setState(137);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(138);
        match(HuskyLangParser::T__2);
        setState(139);
        expression(); 
      }
      setState(144);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

HuskyLangParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuskyLangParser::IdentifierContext::ID() {
  return getToken(HuskyLangParser::ID, 0);
}


size_t HuskyLangParser::IdentifierContext::getRuleIndex() const {
  return HuskyLangParser::RuleIdentifier;
}


antlrcpp::Any HuskyLangParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

HuskyLangParser::IdentifierContext* HuskyLangParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 20, HuskyLangParser::RuleIdentifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(HuskyLangParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

HuskyLangParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuskyLangParser::LiteralContext::getRuleIndex() const {
  return HuskyLangParser::RuleLiteral;
}

void HuskyLangParser::LiteralContext::copyFrom(LiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstantPIContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::ConstantPIContext::PI() {
  return getToken(HuskyLangParser::PI, 0);
}

HuskyLangParser::ConstantPIContext::ConstantPIContext(LiteralContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ConstantPIContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitConstantPI(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstantEContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::ConstantEContext::E() {
  return getToken(HuskyLangParser::E, 0);
}

HuskyLangParser::ConstantEContext::ConstantEContext(LiteralContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::ConstantEContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitConstantE(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoubleContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::DoubleContext::DOUBLE() {
  return getToken(HuskyLangParser::DOUBLE, 0);
}

HuskyLangParser::DoubleContext::DoubleContext(LiteralContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::DoubleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitDouble(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* HuskyLangParser::IntContext::INT() {
  return getToken(HuskyLangParser::INT, 0);
}

HuskyLangParser::IntContext::IntContext(LiteralContext *ctx) { copyFrom(ctx); }


antlrcpp::Any HuskyLangParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HuskyLangVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
HuskyLangParser::LiteralContext* HuskyLangParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 22, HuskyLangParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HuskyLangParser::PI: {
        _localctx = dynamic_cast<LiteralContext *>(_tracker.createInstance<HuskyLangParser::ConstantPIContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(147);
        match(HuskyLangParser::PI);
        break;
      }

      case HuskyLangParser::E: {
        _localctx = dynamic_cast<LiteralContext *>(_tracker.createInstance<HuskyLangParser::ConstantEContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(148);
        match(HuskyLangParser::E);
        break;
      }

      case HuskyLangParser::DOUBLE: {
        _localctx = dynamic_cast<LiteralContext *>(_tracker.createInstance<HuskyLangParser::DoubleContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(149);
        match(HuskyLangParser::DOUBLE);
        break;
      }

      case HuskyLangParser::INT: {
        _localctx = dynamic_cast<LiteralContext *>(_tracker.createInstance<HuskyLangParser::IntContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(150);
        match(HuskyLangParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool HuskyLangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return logicalSempred(dynamic_cast<LogicalContext *>(context), predicateIndex);
    case 3: return compareSempred(dynamic_cast<CompareContext *>(context), predicateIndex);
    case 4: return plusOrMinusSempred(dynamic_cast<PlusOrMinusContext *>(context), predicateIndex);
    case 5: return multOrDivSempred(dynamic_cast<MultOrDivContext *>(context), predicateIndex);
    case 7: return powrSempred(dynamic_cast<PowrContext *>(context), predicateIndex);
    case 9: return argListSempred(dynamic_cast<ArgListContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::logicalSempred(LogicalContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::compareSempred(CompareContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);
    case 7: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::plusOrMinusSempred(PlusOrMinusContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 3);
    case 9: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::multOrDivSempred(MultOrDivContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 10: return precpred(_ctx, 3);
    case 11: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::powrSempred(PowrContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool HuskyLangParser::argListSempred(ArgListContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> HuskyLangParser::_decisionToDFA;
atn::PredictionContextCache HuskyLangParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HuskyLangParser::_atn;
std::vector<uint16_t> HuskyLangParser::_serializedATN;

std::vector<std::string> HuskyLangParser::_ruleNames = {
  "statement", "expression", "logical", "compare", "plusOrMinus", "multOrDiv", 
  "unary", "powr", "atom", "argList", "identifier", "literal"
};

std::vector<std::string> HuskyLangParser::_literalNames = {
  "", "'['", "']'", "','", "", "", "'pi'", "'e'", "'^'", "", "", "'+'", 
  "'-'", "'*'", "'/'", "'='", "'>='", "'>'", "'<='", "'<'", "", "'&'", "'|'", 
  "'!'", "'('", "')'", "", "'\n'"
};

std::vector<std::string> HuskyLangParser::_symbolicNames = {
  "", "", "", "", "INT", "DOUBLE", "PI", "E", "POW", "ID", "CHAR", "PLUS", 
  "MINUS", "MULT", "DIV", "EQUAL", "GTE", "GT", "LTE", "LT", "NEQ", "AND", 
  "OR", "NOT", "LPAR", "RPAR", "WS", "NL"
};

dfa::Vocabulary HuskyLangParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> HuskyLangParser::_tokenNames;

HuskyLangParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1d, 0x9c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x28, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0x2b, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x42, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 
    0x45, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x50, 0xa, 0x6, 0xc, 0x6, 
    0xe, 0x6, 0x53, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x5e, 0xa, 0x7, 
    0xc, 0x7, 0xe, 0x7, 0x61, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x5, 0x8, 0x68, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x70, 0xa, 0x9, 0xc, 0x9, 0xe, 
    0x9, 0x73, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x5, 0xa, 0x7a, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 
    0xa, 0x87, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x7, 0xb, 0x8f, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x92, 0xb, 0xb, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 
    0x9a, 0xa, 0xd, 0x3, 0xd, 0x2, 0x8, 0x6, 0x8, 0xa, 0xc, 0x10, 0x14, 
    0xe, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x2, 0x2, 0x2, 0xa7, 0x2, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1c, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2c, 0x3, 0x2, 0x2, 
    0x2, 0xa, 0x46, 0x3, 0x2, 0x2, 0x2, 0xc, 0x54, 0x3, 0x2, 0x2, 0x2, 0xe, 
    0x67, 0x3, 0x2, 0x2, 0x2, 0x10, 0x69, 0x3, 0x2, 0x2, 0x2, 0x12, 0x86, 
    0x3, 0x2, 0x2, 0x2, 0x14, 0x88, 0x3, 0x2, 0x2, 0x2, 0x16, 0x93, 0x3, 
    0x2, 0x2, 0x2, 0x18, 0x99, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x5, 0x4, 
    0x3, 0x2, 0x1b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0x6, 0x4, 
    0x2, 0x1d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x8, 0x4, 0x1, 0x2, 
    0x1f, 0x20, 0x5, 0x8, 0x5, 0x2, 0x20, 0x29, 0x3, 0x2, 0x2, 0x2, 0x21, 
    0x22, 0xc, 0x5, 0x2, 0x2, 0x22, 0x23, 0x7, 0x17, 0x2, 0x2, 0x23, 0x28, 
    0x5, 0x8, 0x5, 0x2, 0x24, 0x25, 0xc, 0x4, 0x2, 0x2, 0x25, 0x26, 0x7, 
    0x18, 0x2, 0x2, 0x26, 0x28, 0x5, 0x8, 0x5, 0x2, 0x27, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x27, 0x24, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x2d, 0x8, 0x5, 0x1, 0x2, 0x2d, 0x2e, 0x5, 0xa, 0x6, 0x2, 0x2e, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0xc, 0x9, 0x2, 0x2, 0x30, 0x31, 0x7, 
    0x11, 0x2, 0x2, 0x31, 0x42, 0x5, 0xa, 0x6, 0x2, 0x32, 0x33, 0xc, 0x8, 
    0x2, 0x2, 0x33, 0x34, 0x7, 0x16, 0x2, 0x2, 0x34, 0x42, 0x5, 0xa, 0x6, 
    0x2, 0x35, 0x36, 0xc, 0x7, 0x2, 0x2, 0x36, 0x37, 0x7, 0x13, 0x2, 0x2, 
    0x37, 0x42, 0x5, 0xa, 0x6, 0x2, 0x38, 0x39, 0xc, 0x6, 0x2, 0x2, 0x39, 
    0x3a, 0x7, 0x12, 0x2, 0x2, 0x3a, 0x42, 0x5, 0xa, 0x6, 0x2, 0x3b, 0x3c, 
    0xc, 0x5, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x15, 0x2, 0x2, 0x3d, 0x42, 0x5, 
    0xa, 0x6, 0x2, 0x3e, 0x3f, 0xc, 0x4, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x14, 
    0x2, 0x2, 0x40, 0x42, 0x5, 0xa, 0x6, 0x2, 0x41, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x41, 0x32, 0x3, 0x2, 0x2, 0x2, 0x41, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x41, 0x38, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x41, 
    0x3e, 0x3, 0x2, 0x2, 0x2, 0x42, 0x45, 0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x8, 0x6, 
    0x1, 0x2, 0x47, 0x48, 0x5, 0xc, 0x7, 0x2, 0x48, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x49, 0x4a, 0xc, 0x5, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0xd, 0x2, 0x2, 
    0x4b, 0x50, 0x5, 0xc, 0x7, 0x2, 0x4c, 0x4d, 0xc, 0x4, 0x2, 0x2, 0x4d, 
    0x4e, 0x7, 0xe, 0x2, 0x2, 0x4e, 0x50, 0x5, 0xc, 0x7, 0x2, 0x4f, 0x49, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x50, 0x53, 0x3, 
    0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0xb, 0x3, 0x2, 0x2, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x55, 0x8, 0x7, 0x1, 0x2, 0x55, 0x56, 0x5, 0xe, 0x8, 0x2, 
    0x56, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0xc, 0x5, 0x2, 0x2, 0x58, 
    0x59, 0x7, 0xf, 0x2, 0x2, 0x59, 0x5e, 0x5, 0x10, 0x9, 0x2, 0x5a, 0x5b, 
    0xc, 0x4, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0x10, 0x2, 0x2, 0x5c, 0x5e, 0x5, 
    0x10, 0x9, 0x2, 0x5d, 0x57, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5a, 0x3, 0x2, 
    0x2, 0x2, 0x5e, 0x61, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 
    0x2, 0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 0x60, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x7, 0xe, 0x2, 0x2, 0x63, 
    0x68, 0x5, 0x10, 0x9, 0x2, 0x64, 0x65, 0x7, 0x19, 0x2, 0x2, 0x65, 0x68, 
    0x5, 0x10, 0x9, 0x2, 0x66, 0x68, 0x5, 0x10, 0x9, 0x2, 0x67, 0x62, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x64, 0x3, 0x2, 0x2, 0x2, 0x67, 0x66, 0x3, 0x2, 
    0x2, 0x2, 0x68, 0xf, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x8, 0x9, 0x1, 
    0x2, 0x6a, 0x6b, 0x5, 0x12, 0xa, 0x2, 0x6b, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x6d, 0xc, 0x4, 0x2, 0x2, 0x6d, 0x6e, 0x7, 0xa, 0x2, 0x2, 0x6e, 
    0x70, 0x5, 0x12, 0xa, 0x2, 0x6f, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x70, 0x73, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 
    0x2, 0x2, 0x2, 0x72, 0x11, 0x3, 0x2, 0x2, 0x2, 0x73, 0x71, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x87, 0x5, 0x18, 0xd, 0x2, 0x75, 0x87, 0x5, 0x16, 0xc, 
    0x2, 0x76, 0x77, 0x5, 0x16, 0xc, 0x2, 0x77, 0x79, 0x7, 0x1a, 0x2, 0x2, 
    0x78, 0x7a, 0x5, 0x14, 0xb, 0x2, 0x79, 0x78, 0x3, 0x2, 0x2, 0x2, 0x79, 
    0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 
    0x7, 0x1b, 0x2, 0x2, 0x7c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x7, 
    0x1a, 0x2, 0x2, 0x7e, 0x7f, 0x5, 0x4, 0x3, 0x2, 0x7f, 0x80, 0x7, 0x1b, 
    0x2, 0x2, 0x80, 0x87, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x5, 0x16, 0xc, 
    0x2, 0x82, 0x83, 0x7, 0x3, 0x2, 0x2, 0x83, 0x84, 0x5, 0x4, 0x3, 0x2, 
    0x84, 0x85, 0x7, 0x4, 0x2, 0x2, 0x85, 0x87, 0x3, 0x2, 0x2, 0x2, 0x86, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x86, 0x75, 0x3, 0x2, 0x2, 0x2, 0x86, 0x76, 
    0x3, 0x2, 0x2, 0x2, 0x86, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x86, 0x81, 0x3, 
    0x2, 0x2, 0x2, 0x87, 0x13, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x8, 0xb, 
    0x1, 0x2, 0x89, 0x8a, 0x5, 0x4, 0x3, 0x2, 0x8a, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x8b, 0x8c, 0xc, 0x4, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0x5, 0x2, 0x2, 
    0x8d, 0x8f, 0x5, 0x4, 0x3, 0x2, 0x8e, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8f, 
    0x92, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 
    0x3, 0x2, 0x2, 0x2, 0x91, 0x15, 0x3, 0x2, 0x2, 0x2, 0x92, 0x90, 0x3, 
    0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 0xb, 0x2, 0x2, 0x94, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0x95, 0x9a, 0x7, 0x8, 0x2, 0x2, 0x96, 0x9a, 0x7, 0x9, 0x2, 
    0x2, 0x97, 0x9a, 0x7, 0x7, 0x2, 0x2, 0x98, 0x9a, 0x7, 0x6, 0x2, 0x2, 
    0x99, 0x95, 0x3, 0x2, 0x2, 0x2, 0x99, 0x96, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x27, 0x29, 0x41, 0x43, 0x4f, 0x51, 0x5d, 
    0x5f, 0x67, 0x71, 0x79, 0x86, 0x90, 0x99, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

HuskyLangParser::Initializer HuskyLangParser::_init;
