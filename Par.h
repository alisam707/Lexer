#ifndef PAR_H
#define PAR_H

#include "Lex.h"

class Parser : public Lexer
{
  //This class is implemented based on a predictive recursive descent parser(RDP)
  //It has a syntax rule that is required for syntax analysis
  //Starting with RAT17F which is the main function for top-down parser. 
  //Then, calling the next functions recursively to analyze the syntax structure.
public:
  //constructor
  Parser();

  //syntax rule functions after removing left recursive and backtracking

  //<Rat17F> -> <Opt Function Definitions> %%  <Opt Declaration List> <Statement List>
  void RAT23F(ifstream& infile, ofstream& outfile);

  //<Opt Function Definitions> -> <Function Definitions> | <Empty>
  void OptFunctionDefinitions(ifstream& infile, ofstream& outfile);

  //<Function Definitions> -> <Function> < Function Definitions Prime>
  void FunctionDefinitions(ifstream& infile, ofstream& outfile);

  //<Function Definitions Prime>  -> <Function Definitions> | <Empty>  
  void FunctionDefinitionsPrime(ifstream& infile, ofstream& outfile);

  /*<Function> ->  @  <Identifier>  (<Opt Parameter List> )   
  <Opt Declaration List>  <Body>*/
  void Function(ifstream& infile, ofstream& outfile);

  //<Opt Parameter List> ->  <Parameter List>   |  <Empty>
  void OptParameterList(ifstream& infile, ofstream& outfile);

  //<Parameter List>  ->  <Parameter> <Parameter List Prime>
  void ParameterList(ifstream& infile, ofstream& outfile);

  //<Parameter List Prime>  -> , <Parameter List> | <Empty>
  void ParameterListPrime(ifstream& infile, ofstream& outfile);

  //<Parameter> ->  <IDs > : <Qualifier> 
  void Parameter(ifstream& infile, ofstream& outfile);

  //<Qualifier> -> integer   |  boolean  |  floating
  void Qualifier(ifstream& infile, ofstream& outfile);

  //<Body>  ->  {  < Statement List>  }
  void Body(ifstream& infile, ofstream& outfile);

  //<Opt Declaration List> -> <Declaration List>   | <Empty>
  void OptDeclarationList(ifstream& infile, ofstream& outfile);

  //<Declaration List>  -> <Declaration> ;  <Declaration List Prime>
  void DeclarationList(ifstream& infile, ofstream& outfile);

  //<Declaration List Prime>  -> <Declaration List> | <Empty>
  void DeclarationListPrime(ifstream& infile, ofstream& outfile);

  //<Declaration> ->  <Qualifier > <IDs>
  void Declaration(ifstream& infile, ofstream& outfile);

  //<IDs> ->  <Identifier> <IDs Prime>
  void IDs(ifstream& infile, ofstream& outfile);

  //<IDs Prime> ->  , <IDs> | <Empty>
  void IDsPrime(ifstream& infile, ofstream& outfile);

  //<Statement List> ->  <Statement> <Statement List Prime>
  void StatementList(ifstream& infile, ofstream& outfile);

  //<Statement List Prime> ->  <Statement List> | <Empty>
  void StatementListPrime(ifstream& infile, ofstream& outfile);

  /*<Statement> ->  <Compound> | <Assign> | <If> |  <Return> | 
  <Print> | <Read> | <While>*/
  void Statement(ifstream& infile, ofstream& outfile);

  //<Compound> -> {  <Statement List>  }
  void Compound(ifstream& infile, ofstream& outfile);

  //<Assign> -> <Identifier> : = <Expression>;
  void Assign(ifstream& infile, ofstream& outfile);

  //<If> -> if  ( <Condition>  ) <Statement> <If Prime>
  void If(ifstream& infile, ofstream& outfile);

  //<If Prime> ->  fi | else <Statement> fi
  void IfPrime(ifstream& infile, ofstream& outfile);

  //<Return> ->  return <Return Prime>
  void Return(ifstream& infile, ofstream& outfile);

  //<Return Prime> ->  ; |  <Expression> ;
  void ReturnPrime(ifstream& infile, ofstream& outfile);

  //<Print> ->   put ( <Expression>);
  void Print(ifstream& infile, ofstream& outfile);

  //<Read> -> read ( <IDs> );
  void Scan(ifstream& infile, ofstream& outfile);

  //<While> -> while ( <Condition>  )  <Statement> 
  void While(ifstream& infile, ofstream& outfile);

  //<Condition> -> <Expression>  <Relop>   <Expression>
  void Condition(ifstream& infile, ofstream& outfile);

  //<Relop> ->   = |  /=  |   >   | <   |  =>   | <=
  void Relop(ifstream& infile, ofstream& outfile);

  //<Expression>  -> <Term> <Expression Prime>
  void Expression(ifstream& infile, ofstream& outfile);

  /*<Expression Prime>  -> + <Term> <Expression Prime>  |
  - <Term> <Expression Prime> | <Empty>*/
  void ExpressionPrime(ifstream& infile, ofstream& outfile);

  //<Term>    ->  <Factor> <Term Prime>
  void Term(ifstream& infile, ofstream& outfile);

  /*<Term Prime> ->  * <Factor> <Term Prime> |  / <Factor> <Term Prime> |
  <Empty>*/
  void TermPrime(ifstream& infile, ofstream& outfile);

  //<Factor> -> - <Primary>   | <Primary>
  void Factor(ifstream& infile, ofstream& outfile);

  /*<Primary> -> <Identifier> <Primary Prime> | <Integer> | ( <Expression> ) |
  <Real>  | true | false*/
  void Primary(ifstream& infile, ofstream& outfile);

  //<Primary Prime> -> [<IDs>] | <Empty>
  void PrimaryPrime(ifstream& infile, ofstream& outfile);

  //<Empty> -> epsilon
  void Empty(ifstream& infile, ofstream& outfile);

  //Helper functions
  void printError(ofstream& outfile);
  void print(ofstream& outfile);

  //Destructor
  ~Parser();
};

#endif