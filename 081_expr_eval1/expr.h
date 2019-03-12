#include <sstream>
#include <string>
using namespace std;

class Expression
{
 public:
  virtual string toString() const = 0;
  virtual ~Expression() {}
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
};

class PlusExpression : public Expression
{
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual string toString() const {
    stringstream Exp;
    Exp << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return Exp.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
