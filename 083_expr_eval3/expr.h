#include <sstream>
#include <string>
using namespace std;

class Expression
{
 public:
  virtual string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression
{
  long numVal;

 public:
  NumExpression(long num) : numVal(num) {}
  virtual string toString() const {
    stringstream Exp;
    Exp << numVal;
    return Exp.str();
  }
  virtual long evaluate() const { return numVal; }
};

class OpAndNumExpression : public Expression
{
 protected:
  const char * op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpAndNumExpression(const char * op, Expression * lhs, Expression * rhs) :
      op(op),
      lhs(lhs),
      rhs(rhs) {}
  virtual string toString() const {
    stringstream Exp;
    Exp << "(" << lhs->toString() << " " << op << " " << rhs->toString() << ")";
    return Exp.str();
  }
  virtual ~OpAndNumExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpAndNumExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpAndNumExpression("+", lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public OpAndNumExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpAndNumExpression("-", lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public OpAndNumExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpAndNumExpression("*", lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public OpAndNumExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpAndNumExpression("/", lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};
