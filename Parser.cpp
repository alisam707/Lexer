#include "Par.h"

// Constructor: Used for initializing the parser object.
Parser::Parser() {
  // Typically used to initialize member variables, if any.
}

// Print token and lexeme helper function: Prints the current token and lexeme to the output file.
void Parser::print(ofstream &outfile) {
    Lexer::print();  // Call the print function of the Lexer class.
    outfile << "Token: " << left << setw(20) << this->token
            << "Lexeme: " << setw(20) << this->lexeme << endl;
}

// Syntax rule functions follow:

// R1. <Rat23F> ::= <Opt Function Definitions> # <Opt Declaration List> <StatementList> #
// This function parses the RAT23F grammar rule.
void Parser::RAT23F(ifstream &infile, ofstream &outfile) {
  // Get the first token from the input file.
  lexer(infile);
  print(outfile);

  // Writing the production rule to the console and output file.
  cout << "\t<RAT23F> -> <Opt Function Definitions>"
       << " # <Opt Declaration List> <Statement List> #\n";
  outfile << "\t<RAT23F> -> <Opt Function Definitions>"
          << " # <Opt Declaration List> <Statement List> #\n";

  // Parse the optional function definitions, declaration list, and statement list.
  OptFunctionDefinitions(infile, outfile);
  if (lexeme == "#") {
    lexer(infile);
    print(outfile);
    OptDeclarationList(infile, outfile);
    StatementList(infile, outfile);
    if (!(lexeme == "#")) {
      // Error handling for missing EOF marker.
      outfile << "This is not EOF marker.\n"
              << "Error at line " << lineNum << endl
              << "Only <Opt Declaration List> <StatementList> is allowed after "
                 "#.\n";
      cerr << "This is not EOF marker.\n"
           << "Error at line " << lineNum << endl
           << "Only <Opt Declaration List> <StatementList> is allowed after "
              "#.\n";
      exit(1);
    }
    // Reset the line number after finishing syntax checking for a file.
    lineNum = 1;
  } else {
    // Error handling for invalid separator.
    printError(outfile);
    outfile << "Invalid separator, '#' is expected "
            << " after function definitions and before declaration list.\n";
    cerr << "Invalid separator, '#' is expected "
         << " after function definitions and before declaration list.\n";
    exit(1);
  }
}

//R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void Parser::OptFunctionDefinitions(ifstream &infile, ofstream &outfile) {
  if (lexeme == "function") {

      outfile << "\t<Opt Function Definition> -> "
              << "<Function Definition>\n";
      cout << "\t<Opt Function Definition> -> "
           << "<Function Definition>\n";

    FunctionDefinitions(infile, outfile);
  } else {

      outfile << "\t<Opt Function Definition> -> "
              << "Epsilon" << endl;
      cout << "\t<Opt Function Definition> -> "
           << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R3. <Function Definitions> ::= <Function> <Function Definitions'>
void Parser::FunctionDefinitions(ifstream &infile, ofstream &outfile) {

    outfile << "\t<Function Definition> ->"
            << " <Function> <Function Definition Prime>\n";
    cout << "\t<Function Definition> ->"
         << " <Function> <Function Definition Prime>\n";

  Function(infile, outfile);
  FunctionDefinitionsPrime(infile, outfile);
}

//R4. <Function Definitions'> ::= <Function Definitions> | <Empty>
void Parser::FunctionDefinitionsPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "function") {

      cout << "\t<Function Definition Prime> ->"
           << " <Function Definition>\n";
      outfile << "\t<Function Definition Prime> ->"
              << " <Function Definition>\n";

    FunctionDefinitions(infile, outfile);
  } else {

      cout << "\t<Function Definition Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Function Definition Prime> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R5. <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt DeclarationList> <Body>
void Parser::Function(ifstream &infile, ofstream &outfile) {
  if (lexeme == "function") {

      cout << "\t<Function> ->"
           << " function <Identifier> (<Opt Parameter List>)"
           << " <Opt Declaration List> <Body>\n";
      outfile << "\t<Function> ->"
              << " function <Identifier> (<Opt Parameter List>)"
              << " <Opt Declaration List> <Body>\n";

    lexer(infile);
    print(outfile);
    if (token == "identifier") {
      lexer(infile);
      print(outfile);
      if (lexeme == "(") {
        lexer(infile);
        print(outfile);
        OptParameterList(infile, outfile);
        if (lexeme == ")") {
          lexer(infile);
          print(outfile);
          OptDeclarationList(infile, outfile);
          Body(infile, outfile);
        } else {
          printError(outfile);
          outfile << "Function syntax error\n";
          outfile << "Invalid separator, ')' is expected"
                  << " after parameter list.\n";
          cerr << "Function syntax error\n";
          cerr << "Invalid separator, ')' is expected"
               << " after parameter list.\n";

          exit(1);
        }
      } else {
        printError(outfile);
        outfile << "Function syntax error\n";
        outfile << "Invalid separator, '(' is expected"
                << " after <identifier> and before parameter list.\n";
        cerr << "Function syntax error\n";
        cerr << "Invalid separator, '(' is expected"
             << " after <identifier> and before parameter list.\n";

        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "Function syntax error\n";
      outfile << "Invalid token, <identifier> is expected after 'function'.\n";
      cerr << "Function syntax error\n";
      cerr << "Invalid token, <identifier> is expected after 'function'.\n";

      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Function syntax error\n";
    outfile << "Invalid separator, 'function' is expected"
            << " at the beginning of a function.\n";
    cerr << "Function syntax error\n";
    cerr << "Invalid separator, 'function' is expected"
         << " at the beginning of a function.\n";

    exit(1);
  }
}

//R6. <Opt Parameter List> ::= <Parameter List> | <Empty>
void Parser::OptParameterList(ifstream &infile, ofstream &outfile) {
  if (token == "identifier") {

      cout << "\t<Opt Parameter List> -> "
           << "<Parameter List>\n";
      outfile << "\t<Opt Parameter List> -> "
              << "<Parameter List>\n";

    ParameterList(infile, outfile);
  } else {

      cout << "\t<Opt Parameter List> -> "
           << "Epsilon" << endl;
      outfile << "\t<Opt Parameter List> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R7. <Parameter List> ::= <Parameter> <Parameter List'>
void Parser::ParameterList(ifstream &infile, ofstream &outfile) {

    cout << "\t<Parameter List> -> "
         << "<Parameter> <Parameter List Prime>\n";
    outfile << "\t<Parameter List> -> "
            << "<Parameter> <Parameter List Prime>\n";

  Parameter(infile, outfile);
  ParameterListPrime(infile, outfile);
}

//R8. <Parameter List'> ::= , <Parameter List> | <Empty>
void Parser::ParameterListPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == ",") {

      cout << "\t<Parameter List Prime> -> "
           << ", <Parameter>\n";
      outfile << "\t<Parameter List Prime> -> "
              << ", <Parameter>\n";

    lexer(infile);
    print(outfile);
    ParameterList(infile, outfile);
  } else {

      cout << "\t<Parameter List Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Parameter List Prime> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R9. <Parameter> ::= <IDs> <Qualifier>
void Parser::Parameter(ifstream &infile, ofstream &outfile) {
  if (token == "identifier") {

      cout << "\t<Parameter> -> <IDs> <Qualifier>\n";
      outfile << "\t<Parameter> -> <IDs> <Qualifier>\n";

    IDs(infile, outfile);
    Qualifier(infile, outfile);
  } else {
    printError(outfile);
    outfile << "Parameter syntax error\n";
    outfile << "Invalid token, <identifier> is expected"
            << " after '(' and before ')'.\n";
    cerr << "Parameter syntax error\n";
    cerr << "Invalid token, <identifier> is expected"
         << " after '(' and before ')'.\n";

    exit(1);
  }
}

//R10. <Qualifier> ::= integer | bool | real
void Parser::Qualifier(ifstream &infile, ofstream &outfile) {
  if (token == "keyword" && lexeme == "integer") {

      cout << "\t<Qualifier> -> integer\n";
      outfile << "\t<Qualifier> -> integer\n";

    lexer(infile);
    print(outfile);
  } else if (token == "keyword" && lexeme == "bool") {

      cout << "\t<Qualifier> -> bool\n";
      outfile << "\t<Qualifier> -> bool\n";

    lexer(infile);
    print(outfile);
  } else if (token == "keyword" && lexeme == "real") {

      cout << "\t<Qualifier> -> real\n";
      outfile << "\t<Qualifier> -> real\n";

    lexer(infile);
    print(outfile);
  } else {
    printError(outfile);
    outfile << "Qualifier syntax error\n"
            << "Invalid keyword\n";
    outfile << "'integer', 'bool' or 'real' keyword is expected"
            << " after identifier.\n";
    cerr << "Qualifier syntax error\n"
         << "Invalid keyword\n";
    cerr << "'integer', 'bool' or 'real' keyword is expected"
         << " after identifier.\n";

    exit(1);
  }
}

//R11. <Body> ::= { <Statement List> }
void Parser::Body(ifstream &infile, ofstream &outfile) {
  if (lexeme == "{") {

      cout << "\t<Body> -> { <Statement List> }\n";
      outfile << "\t<Body> -> { <Statement List> }\n";

    lexer(infile);
    print(outfile);
    StatementList(infile, outfile);
    if (lexeme == "}") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "Function Body syntax error\n";
      outfile << "Invalid separator, '}' is expected"
              << " after statements.\n";
      cerr << "Function Body syntax error\n";
      cerr << "Invalid separator, '}' is expected"
           << " after statements.\n";

      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Function Body syntax error";
    outfile << "Invalid separator, '{' is expected"
            << " before any statements.\n";
    cerr << "Function Body syntax error";
    cerr << "Invalid separator, '{' is expected"
         << " before any statements.\n";

    exit(1);
  }
}

//R12. <Opt Declaration List> ::= <Declaration List> | <Empty>
void Parser::OptDeclarationList(ifstream &infile, ofstream &outfile) {
  if (lexeme == "integer" || lexeme == "bool" || lexeme == "real") {

      cout << "\t<Opt Declaration List> -> <Declaration List>\n";
      outfile << "\t<Opt Declaration List> -> <Declaration List>\n";

    DeclarationList(infile, outfile);
  } else {

      cout << "\t<Opt Declaration List> -> "
           << "Epsilon" << endl;
      outfile << "\t<Opt Declaration List> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R13. <Declaration List> ::= <Declaration> ; <Declaration List'>
void Parser::DeclarationList(ifstream &infile, ofstream &outfile) {

    cout << "\t<Declaration List> -> "
         << "<Declaration> ; <Declaration List Prime>\n";
    outfile << "\t<Declaration List> -> "
            << "<Declaration> ; <Declaration List Prime>\n";

  Declaration(infile, outfile);
  if (lexeme == ";") {
    lexer(infile);
    print(outfile);
    DeclarationListPrime(infile, outfile);
  } else {
    printError(outfile);
    outfile << "Declaration List syntax error\n";
    outfile << "Invalid separator, ';' is expected"
            << " at the end of declaration.\n";
    cerr << "Declaration List syntax error\n";
    cerr << "Invalid separator, ';' is expected"
         << " at the end of declaration.\n";

    exit(1);
  }
}

//R14. <Declaration List'> ::= <Declaration List> | <Empty>
void Parser::DeclarationListPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "integer" || lexeme == "bool" || lexeme == "real") {

      cout << "\t<Declaration List Prime> -> "
           << "<Declaration List>\n";
      outfile << "\t<Declaration List Prime> -> "
              << "<Declaration List>\n";

    DeclarationList(infile, outfile);
  } else {

      cout << "\t<Declaration List Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Declaration List Prime> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R15. <Declaration> ::= <Qualifier> <IDs>
void Parser::Declaration(ifstream &infile, ofstream &outfile) {

    cout << "\t<Declaration> -> "
         << "<Qualifier> <IDs>\n";
    outfile << "\t<Declaration> -> "
            << "<Qualifier> <IDs>\n";

  Qualifier(infile, outfile);
  IDs(infile, outfile);
}

//R16. <IDs> ::= <Identifier> <IDs'>
void Parser::IDs(ifstream &infile, ofstream &outfile) {
  if (token == "identifier") {

      cout << "\t<IDs> -> "
           << "<identifier> <IDs Prime>\n";
      outfile << "\t<IDs> -> "
              << "<identifier> <IDs Prime>\n";

    lexer(infile);
    print(outfile);
    IDsPrime(infile, outfile);
  } else {
    printError(outfile);
    outfile << "IDs syntax error\n";
    outfile << "Invalid token, <identifier> is expected"
               " after '(' or ','.\n";
    cerr << "IDs syntax error\n";
    cerr << "Invalid token, <identifier> is expected"
            " after '(' or ','.\n";

    exit(1);
  }
}

//R17. <IDs'> ::= , <IDs> | <Empty>
void Parser::IDsPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == ",") {

      cout << "\t<IDsPrime> -> "
           << ", <IDs>\n";
      outfile << "\t<IDsPrime> -> "
              << ", <IDs>\n";

    lexer(infile);
    print(outfile);
    IDs(infile, outfile);
  } else {

      cout << "\t<IDs Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<IDs Prime> -> "
              << "Epsilon" << endl;

    Empty(infile, outfile);
  }
}

//R18. <Statement List> ::= <Statement> <Statement List'>
void Parser::StatementList(ifstream &infile, ofstream &outfile) {
    cout << "\t<Statement List> -> "
         << "<Statement> <Statement List Prime>\n";
    outfile << "\t<Statement List> -> "
            << "<Statement> <Statement List Prime>\n";

  Statement(infile, outfile);
  StatementListPrime(infile, outfile);
}

//R19. <Statement List'> ::= <Statement List> | <Empty>
void Parser::StatementListPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "{" || token == "identifier" || 
      lexeme == "ret" || lexeme == "put" || lexeme == "put" ||
      lexeme == "get" || lexeme == "while") {
      cout << "\t<Statement List Prime> -> "
           << "<Statement List>\n";
      outfile << "\t<Statement List Prime> -> "
              << "<Statement List>\n";
  
    StatementList(infile, outfile);
  } else {
    if (!(lexeme == "EOF")) {
      cout << "\t<Statement List Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Statement List Prime> -> "
              << "Epsilon" << endl;
  }
    Empty(infile, outfile);
  }
}

//R20. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Parser::Statement(ifstream &infile, ofstream &outfile) {
  if (lexeme == "{") {
      cout << "\t<Statement> -> "
           << "<Compound>\n";
      outfile << "\t<Statement> -> "
              << "<Compound>\n";
  
    Compound(infile, outfile);
  } else if (token == "identifier") {
      cout << "\t<Statement> -> "
           << "<Assign>\n";
      outfile << "\t<Statement> -> "
              << "<Assign>\n";
  
    Assign(infile, outfile);
  } else if (lexeme == "if") {
      cout << "\t<Statement> -> "
           << "<If>\n";
      outfile << "\t<Statement> -> "
              << "<If>\n";
  
    If(infile, outfile);
  } else if (lexeme == "ret") {
      cout << "\t<Statement> -> "
           << "<Return>\n";
      outfile << "\t<Statement> -> "
              << "<Return>\n";
  
    Return(infile, outfile);
  } else if (lexeme == "put") {
      cout << "\t<Statement> -> "
           << "<Print>\n";
      outfile << "\t<Statement> -> "
              << "<Print>\n";
  
    Print(infile, outfile);
  } else if (lexeme == "get") {
      cout << "\t<Statement> -> "
           << "<Scan>\n";
      outfile << "\t<Statement> -> "
              << "<Scan>\n";
  
    Scan(infile, outfile);
  } else if (lexeme == "while") {
      cout << "\t<Statement> -> "
           << "<While>\n";
      outfile << "\t<Statement> -> "
              << "<While>\n";
  
    While(infile, outfile);
  } else {
    printError(outfile);
    outfile << "Statement syntax error\n";
    outfile << "Invalid token or keyword or separator\n";
    outfile << "<identifier>,'if', 'ret', 'put', 'get','while' "
            << "keyword or '{'is expected at the beginning of a statement.\n";
    cerr << "Statement syntax error\n";
    cerr << "Invalid token or keyword or separator\n";
    cerr << "<identifier>,'if', 'ret', 'put', 'get','while' "
         << "keyword or '{'is expected at the beginning of a statement.\n";
    exit(1);
  }
}

//R21. <Compound> ::= { <Statement List> }
void Parser::Compound(ifstream &infile, ofstream &outfile) {
  if (lexeme == "{") {
      cout << "\t<Compound> -> "
           << "{ <StatementList> }\n";
      outfile << "\t<Compound> -> "
              << "{ <StatementList> }\n";
  
    lexer(infile);
    print(outfile);
    StatementList(infile, outfile);
    if (lexeme == "}") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "Compound syntax error\n";
      outfile << "Invalid separator, '}' is expected"
              << " at the end of statement list.\n";
      cerr << "Compound syntax error\n";
      cerr << "Invalid separator, '}' is expected"
           << " at the end of statement list.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Compound syntax error\n";
    outfile << "Invalid separator, '{' is expected"
            << " at the beginning of statement list.\n";
    cerr << "Compound syntax error\n";
    cerr << "Invalid separator, '{' is expected"
         << " at the beginning of statement list.\n";
    exit(1);
  }
}

//R22. <Assign> ::= <Identifier> = <Expression> ;
void Parser::Assign(ifstream &infile, ofstream &outfile) {
  if (token == "identifier") {
      cout << "\t<Assign> -> "
           << "<Identifier> = <Expression>;\n";
      outfile << "\t<Assign> -> "
              << "<Identifier> = <Expression>;\n";
  
    lexer(infile);
    print(outfile);
    if (lexeme == "=") {
      lexer(infile);
      print(outfile);
      Expression(infile, outfile);
      if (lexeme == ";") {
        lexer(infile);
        print(outfile);
      } else {
        printError(outfile);
        outfile << "Assign syntax error\n";
        outfile << "Invalid separator, ';' is expected"
                   " at the end of assign statement.\n";
        cerr << "Assign syntax error\n";
        cerr << "Invalid separator, ';' is expected"
                " at the end of assign statement.\n";
        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "Assign syntax error\n";
      outfile << "Invalid operator, '=' is expected"
              << " after <identifier> and before <expression>.\n";
      cerr << "Assign syntax error\n";
      cerr << "Invalid operator, '=' is expected"
           << " after <identifier> and before <expression>.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Assign syntax error\n";
    outfile << "Invalid token, <identifier> is expected"
               " at the beginning of assign statement.\n";
    cerr << "Assign syntax error\n";
    cerr << "Invalid token, <identifier> is expected"
            " at the beginning of assign statement.\n";
    exit(1);
  }
}

//R23. <If> ::= if ( <Condition> ) <Statement> <If’>
void Parser::If(ifstream &infile, ofstream &outfile) {
  if (lexeme == "if") {
      cout << "\t<If> -> "
           << "if (<Condition>) <Statement> <If Prime>\n";
      outfile << "\t<If> -> "
              << "if (<Condition>) <Statement> <If Prime>\n";
  
    lexer(infile);
    print(outfile);
    if (lexeme == "(") {
      lexer(infile);
      print(outfile);
      Condition(infile, outfile);
      if (lexeme == ")") {
        lexer(infile);
        print(outfile);
        Statement(infile, outfile);
        IfPrime(infile, outfile);
      } else {
        printError(outfile);
        outfile << "If statement syntax error\n";
        outfile << "Invalid separator, ')' is expected"
                << " after condition.\n";
        cerr << "If statement syntax error\n";
        cerr << "Invalid separator, ')' is expected"
             << " after condition.\n";
        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "If statement syntax error\n";
      outfile << "Invalid separator, '(' is expected"
              << " before condition.\n";
      cerr << "If statement syntax error\n";
      cerr << "Invalid separator, '(' is expected"
           << " before condition.\n";

      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "If statement syntax error\n";
    outfile << "Invalid keyword, 'if' keyword is expected"
            << " at the beginning of If statement.\n";
    cerr << "If statement syntax error\n";
    cerr << "Invalid keyword, 'if' keyword is expected"
         << " at the beginning of If statement.\n";
    exit(1);
  }
}

//R24. <If’> ::= endif | else <Statement> endif
void Parser::IfPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "endif") {
      cout << "\t<If Prime> -> "
           << "endif\n";
      outfile << "\t<If Prime> -> "
              << "endif\n";
  
    lexer(infile);
    print(outfile);
  } else if (lexeme == "else") {
      cout << "\t<If Prime> -> "
           << "else <Statement> endif\n";
      outfile << "\t<If Prime> -> "
              << "else <Statement> endif\n";
  
    lexer(infile);
    print(outfile);
    Statement(infile, outfile);
    if (lexeme == "endif") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "If statement syntax error\n";
      outfile << "Invalid keyword, 'endif' is expected"
              << " at the end of If statement.\n";
      cerr << "If statement syntax error\n";
      cerr << "Invalid keyword, 'endif' is expected"
           << " at the end of If statement.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "If statement syntax error\n";
    outfile << "Invalid keyword, 'endif' is expected at the end of If Statement\n"
            << "Or 'else' is expected if there is an If-else statement.\n";
    cerr << "If statement syntax error\n";
    cerr << "Invalid keyword, 'endif' is expected at the end of If Statement\n"
         << "Or 'else' is expected if there is an If-else statement.\n";
    exit(1);
  }
}

//R25. <Return> ::= ret <Return’>
void Parser::Return(ifstream &infile, ofstream &outfile) {
  if (lexeme == "ret") {
      cout << "\t<Return> -> "
           << "ret <Return Prime>\n";
      outfile << "\t<Return> -> "
              << "ret <Return Prime>\n";
  
    lexer(infile);
    print(outfile);
    ReturnPrime(infile, outfile);
  } else {
    printError(outfile);
    outfile << "Return statement syntax error\n";
    outfile << "Invalid keyword, 'ret' is expected"
            << " at the beginning of Return statement.\n";
    cerr << "Return statement syntax error\n";
    cerr << "Invalid keyword, 'ret' is expected"
         << " at the beginning of Return statement.\n";
    exit(1);
  }
}

//R26. <Return’> ::= ; | ret <Expression> ;
void Parser::ReturnPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == ";") {
      cout << "\t<Return Prime> -> "
           << ";\n";
      outfile << "\t<Return Prime> -> "
              << ";\n";
  
    lexer(infile);
    print(outfile);
  } else {
      cout << "\t<Return Prime> -> "
           << "<Expression>;\n";
      outfile << "\t<Return Prime> -> "
              << "<Expression>;\n";
  
    Expression(infile, outfile);
    if (lexeme == ";") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "Return statement syntax error\n";
      outfile << "Invalid separator, ';' is expected"
              << " at the end of Return statement.\n";
      cerr << "Return statement syntax error\n";
      cerr << "Invalid separator, ';' is expected"
           << " at the end of Return statement.\n";
      exit(1);
    }
  }
}

//R27. <Print> ::= put ( <Expression>);
void Parser::Print(ifstream &infile, ofstream &outfile) {
  if (lexeme == "put") {
      cout << "\t<Print> -> "
           << "put (<Expression>);\n";
      outfile << "\t<Print> -> "
              << "put (<Expression>);\n";
  
    lexer(infile);
    print(outfile);
    if (lexeme == "(") {
      lexer(infile);
      print(outfile);
      Expression(infile, outfile);
      if (lexeme == ")") {
        lexer(infile);
        print(outfile);
        if (lexeme == ";") {
          lexer(infile);
          print(outfile);
        } else {
          printError(outfile);
          outfile << "Print statement syntax error\n";
          outfile << "Invalid separator, ';' is expected"
                  << " at the end of Print statement.\n";
          cerr << "Print statement syntax error\n";
          cerr << "Invalid separator, ';' is expected"
               << " at the end of Print statement.\n";
          exit(1);
        }
      } else {
        printError(outfile);
        outfile << "Print statement syntax error\n";
        outfile << "Invalid separator, ')' is expected"
                << " before ';' and after <Expression>.\n";
        cerr << "Print statement syntax error\n";
        cerr << "Invalid separator, ')' is expected"
             << " before ';' and after <Expression>.\n";
        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "Print statement syntax error\n";
      outfile << "Invalid separator, '(' is expected"
              << " after 'put' keyword and before <Expression>.\n";
      cerr << "Print statement syntax error\n";
      cerr << "Invalid separator, '(' is expected"
           << " after 'put' keyword and before <Expression>.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Print statement syntax error\n";
    outfile << "Invalid keyword, 'put' is expected"
            << " at the beginning of Print statement.\n";
    cerr << "Print statement syntax error\n";
    cerr << "Invalid keyword, 'put' is expected"
         << " at the beginning of Print statement.\n";
    exit(1);
  }
}

//R28. <Scan> ::= get ( <IDs> );
void Parser::Scan(ifstream &infile, ofstream &outfile) {
  if (lexeme == "get") {
      cout << "\t<Scan> -> "
           << "get (<IDs>);\n";
      outfile << "\t<Scan> -> "
              << "get (<IDs>);\n";
  
    lexer(infile);
    print(outfile);
    if (lexeme == "(") {
      lexer(infile);
      print(outfile);
      IDs(infile, outfile);
      if (lexeme == ")") {
        lexer(infile);
        print(outfile);
        if (lexeme == ";") {
          lexer(infile);
          print(outfile);
        } else {
          printError(outfile);
          outfile << "Scan statement syntax error\n";
          outfile << "Invalid separator, ';' is expected"
                  << " at the end of Scan statement.\n";
          cerr << "Scan statement syntax error\n";
          cerr << "Invalid separator, ';' is expected"
               << " at the end of Scan statement.\n";
          exit(1);
        }
      } else {
        printError(outfile);
        outfile << "Scan statement syntax error\n";
        outfile << "Invalid separator, ')' is expected"
                << " after <IDs> and before ';'.\n";
        cerr << "Scan statement syntax error\n";
        cerr << "Invalid separator, ')' is expected"
             << " after <IDs> and before ';'.\n";
        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "Scan statement syntax error\n";
      outfile << "Invalid separator, '(' is expected"
              << " after 'get' keyword and before <IDs>.\n";
      cerr << "Scan statement syntax error\n";
      cerr << "Invalid separator, '(' is expected"
           << " after 'get' keyword and before <IDs>.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "Scan statement syntax error\n";
    outfile << "Invalid keyword, 'get' is expected"
            << " at the beginning of Scan statement.\n";
    cerr << "Scan statement syntax error\n";
    cerr << "Invalid keyword, 'get' is expected"
         << " at the beginning of Scan statement.\n";
    exit(1);
  }
}

//R29. <While> ::= while ( <Condition> ) <Statement>
void Parser::While(ifstream &infile, ofstream &outfile) {
  if (lexeme == "while") {
      cout << "\t<While> -> "
           << "<while (<Condition>) <Statement>\n";
      outfile << "\t<While> -> "
              << "<while (<Condition>) <Statement>\n";
    lexer(infile);
    print(outfile);
    if (lexeme == "(") {
      lexer(infile);
      print(outfile);
      Condition(infile, outfile);
      if (lexeme == ")") {
        lexer(infile);
        print(outfile);
        Statement(infile, outfile);
      } else {
        printError(outfile);
        outfile << "While statement syntax error\n";
        outfile << "Invalid separator, ')' is expected"
                << " after condition and before any statements.\n";
        cerr << "While statement syntax error\n";
        cerr << "Invalid separator, ')' is expected"
             << " after condition and before any statements.\n";
        exit(1);
      }
    } else {
      printError(outfile);
      outfile << "While statement syntax error\n";
      outfile << "Invalid separator, '(' is expected"
              << " before condition and after 'while' keyword.\n";
      cerr << "While statement syntax error\n";
      cerr << "Invalid separator, '(' is expected"
           << " before condition and after 'while' keyword.\n";
      exit(1);
    }
  } else {
    printError(outfile);
    outfile << "While-loop syntax error\n";
    outfile << "Invalid keyword, 'while' is expected"
            << " at the beginning of While-loop.\n";
    cerr << "While-loop syntax error\n";
    cerr << "Invalid keyword, 'while' is expected"
         << " at the beginning of While-loop.\n";
    exit(1);
  }
}

//R30. <Condition> ::= <Expression> <Relop> <Expression>
void Parser::Condition(ifstream &infile, ofstream &outfile) {
    cout << "\t<Condition> -> "
         << "<Expression> <Relop> <Expression>\n";
    outfile << "\t<Condition> -> "
            << "<Expression> <Relop> <Expression>\n";
  Expression(infile, outfile);
  Relop(infile, outfile);
  Expression(infile, outfile);
}

//R31. <Relop> ::= == | != | > | < | <= | =>
void Parser::Relop(ifstream &infile, ofstream &outfile) {
  if (lexeme == "==") {
      cout << "\t<Relop> -> =\n";
      outfile << "\t<Relop> -> =\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "!=") {
      cout << "\t<Relop> -> /=\n";
      outfile << "\t<Relop> -> /=\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == ">") {
      cout << "\t<Relop> -> >\n";
      outfile << "\t<Relop> -> >\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "<") {
      cout << "\t<Relop> -> <\n";
      outfile << "\t<Relop> -> <\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "=>") {
      cout << "\t<Relop> -> =>\n";
      outfile << "\t<Relop> -> =>\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "<=") {
      cout << "\t<Relop> -> <=\n";
      outfile << "\t<Relop> -> <=\n";
    lexer(infile);
    print(outfile);
  } else {
    printError(outfile);
    outfile << "Relop syntax error\n";
    outfile << "Invalid operator\n"
            << "'==', '!=', '>', '<', '=>' or '<=' is expected"
            << " between 2 <Expression>.\n";
    cerr << "Relop syntax error\n";
    cerr << "Invalid operator\n"
         << "'==', '!=', '>', '<', '=>' or '<=' is expected"
         << " between 2 <Expression>.\n";
    exit(1);
  }
}

//R32. <Expression> ::= <Term> <Expression'>
void Parser::Expression(ifstream &infile, ofstream &outfile) {
    cout << "\t<Expression> -> <Term> <Expression Prime>\n";
    outfile << "\t<Expression> -> <Term> <Expression Prime>\n";
  Term(infile, outfile);
  ExpressionPrime(infile, outfile);
}

//R33. <Expression'> ::= + <Term> <Expression'> | - <Term> <Expression'> | <Empty>
void Parser::ExpressionPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "+") {
      cout << "\t<Expression Prime> -> "
           << "+ <Term> <Expression Prime>\n";
      outfile << "\t<Expression Prime> -> "
              << "+ <Term> <Expression Prime>\n";
    lexer(infile);
    print(outfile);
    Term(infile, outfile);
    ExpressionPrime(infile, outfile);
  } else if (lexeme == "-") {
      cout << "\t<Expression Prime> -> "
           << "- <Term> <Expression Prime>\n";
      outfile << "\t<Expression Prime> -> "
              << "- <Term> <Expression Prime>\n";
    lexer(infile);
    print(outfile);
    Term(infile, outfile);
    ExpressionPrime(infile, outfile);
  } else {
      cout << "\t<Expression Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Expression Prime> -> "
              << "Epsilon" << endl;
    Empty(infile, outfile);
  }
}

//R34. <Term> ::= <Factor> <Term'>
void Parser::Term(ifstream &infile, ofstream &outfile) {
    cout << "\t<Term> -> <Factor> <Term Prime>\n";
    outfile << "\t<Term> -> <Factor> <Term Prime>\n";
  Factor(infile, outfile);
  TermPrime(infile, outfile);
}

//R35. <Term'> ::= * <Factor> <Term'> | / <Factor> <Term'> | <Empty>
void Parser::TermPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "*") {
      cout << "\t<Term Prime> -> * <Factor> <Term Prime>\n";
      outfile << "\t<Term Prime> -> * <Factor> <Term Prime>\n";
    lexer(infile);
    print(outfile);
    Factor(infile, outfile);
    TermPrime(infile, outfile);
  } else if (lexeme == "/") {
      cout << "\t<Term Prime> -> / <Factor> <Term Prime>\n";
      outfile << "\t<Term Prime> -> / <Factor> <Term Prime>\n";
    lexer(infile);
    print(outfile);
    Factor(infile, outfile);
    TermPrime(infile, outfile);
  } else {
      cout << "\t<Term Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Term Prime> -> "
              << "Epsilon" << endl;
    Empty(infile, outfile);
  }
}

//R36. <Factor> ::= - <Primary> | <Primary>
void Parser::Factor(ifstream &infile, ofstream &outfile) {
  if (lexeme == "-") {
      cout << "\t<Factor> -> - <Primary>\n";
      outfile << "\t<Factor> -> - <Primary>\n";
    lexer(infile);
    print(outfile);
    Primary(infile, outfile);
  } else {
      cout << "\t<Factor> -> <Primary>\n";
      outfile << "\t<Factor> -> <Primary>\n";
    Primary(infile, outfile);
  }
}

//R37. <Primary> ::= <Identifier> <Primary’>| <Integer> | (<Expression>) | <Real> | true | false
void Parser::Primary(ifstream &infile, ofstream &outfile) {
  if (token == "identifier") {
      cout << "\t<Primary> -> <identifier> <Primary Prime>\n";
      outfile << "\t<Primary> -> <identifier> <Primary Prime>\n";
    lexer(infile);
    print(outfile);
    PrimaryPrime(infile, outfile);
  } else if (token == "integer") {
      cout << "\t<Primary> -> <integer>\n";
      outfile << "\t<Primary> -> <integer>\n";
    lexer(infile);
    print(outfile);
  } else if (token == "real") {
      cout << "\t<Primary> -> <real>\n";
      outfile << "\t<Primary> -> <real>\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "(") {
      cout << "\t<Primary> -> (<Expression>)\n";
      outfile << "\t<Primary> -> (<Expression>)\n";
    lexer(infile);
    print(outfile);
    Expression(infile, outfile);
    if (lexeme == ")") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "Invalid separator, ')' is expected.\n";
      cerr << "Invalid separator, ')' is expected.\n";
      exit(1);
    }
  } else if (lexeme == "true") {
      cout << "\t<Prime> -> true\n";
      outfile << "\t<Prime> -> true\n";
    lexer(infile);
    print(outfile);
  } else if (lexeme == "false") {
      cout << "\t<Prime> -> false\n";
      outfile << "\t<Prime> -> false\n";
    lexer(infile);
    print(outfile);
  } else {
    printError(outfile);
    outfile << "Primary syntax error\n";
    outfile << "Invalid token, separator, or boolean value\n";
    outfile << "<identifier>, <integer>, <real>, "
            << "'(', 'true' or 'false' is expected"
            << " after '+', '-', '*' or '/'.\n";
    cerr << "Primary syntax error\n";
    cerr << "Invalid token, separator, or boolean value\n";
    cerr << "<identifier>, <integer>, <real>, "
         << "'(', 'true' or 'false' is expected"
         << " after '+', '-', '*' or '/'.\n";
    exit(1);
  }
}

//R38. <Primary’> ::=  ( <IDs> ) | <Empty>
void Parser::PrimaryPrime(ifstream &infile, ofstream &outfile) {
  if (lexeme == "(") {
      cout << "\t<Primary Prime> -> (<IDs>)\n";
      outfile << "\t<Primary Prime> -> (<IDs>)\n";
    lexer(infile);
    print(outfile);
    IDs(infile, outfile);
    if (lexeme == ")") {
      lexer(infile);
      print(outfile);
    } else {
      printError(outfile);
      outfile << "Primary syntax error\n";
      outfile << "Invalid separator, ')' is expected"
              << " after <IDs>.\n";
      cerr << "Primary syntax error\n";
      cerr << "Invalid separator, ')' is expected"
           << " after <IDs>.\n";
      exit(1);
    }
  } else {
      cout << "\t<Primary Prime> -> "
           << "Epsilon" << endl;
      outfile << "\t<Primary Prime> -> "
              << "Epsilon" << endl;
    Empty(infile, outfile);
  }
}

//R39. <Empty> ::= epsilon
void Parser::Empty(ifstream &infile, ofstream &outfile) {
  // Do nothing in this function
}

void Parser::printError(ofstream &outfile) {
  outfile << "Error at line " << lineNum << endl;
  cerr << "Error at line " << lineNum << endl;
  // Reset the line number if there is an syntax error. 
  lineNum = 1;
}

// Destructor
Parser::~Parser(){}
