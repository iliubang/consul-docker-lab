//=====================================================================
//
// ast.h -
//
// Created by liubang on 2023/11/02 15:00
// Last Modified: 2023/11/02 15:00
//
//=====================================================================
#pragma once

#include <chrono>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "token.h"

namespace pl {

struct Position;
struct SourceLocation;
struct Comment;
struct BaseNode;
struct Attribute;
struct AttributeParam;
struct Package;
struct File;
struct PackageClause;
struct ImportDeclaration;
struct Block;
struct BadStmt;
struct ExprStmt;
struct ReturnStmt;
struct OptionStmt;
struct BuiltinStmt;
struct NamedType;
struct TvarType;
struct ArrayType;
struct StreamType;
struct VectorType;
struct DictType;
struct DynamicType;
struct FunctionType;
struct TypeExpression;
struct TypeConstraint;
struct RecordType;
struct PropertyType;
struct TestCaseStmt;
struct VariableAssgn;
struct MemberAssgn;
struct StringExpr;
struct TextPart;
struct InterpolatedPart;
struct ParenExpr;
struct CallExpr;
struct PipeExpr;
struct MemberExpr;
struct IndexExpr;
struct FunctionExpr;
struct BinaryExpr;
struct UnaryExpr;
struct LogicalExpr;
struct ArrayItem;
struct ArrayExpr;
struct DictExpr;
struct DictItem;
struct WithSource;
struct ObjectExpr;
struct ConditionalExpr;
struct BadExpr;
struct Property;
struct Identifier;
struct PipeLit;
struct StringLit;
struct BooleanLit;
struct FloatLit;
struct IntegerLit;
struct UintLit;
struct LabelLit;
struct RegexpLit;
struct Duration;
struct DurationLit;
struct DateTimeLit;

struct Expression;
struct Statement;
struct Assignment;
struct PropertyKey;
struct FunctionBody;
struct MonoType;
struct ParameterType;
struct StringExprPart;

enum class Operator;
enum class LogicalOperator;

struct BaseNode {
    // implementation details
    SourceLocation location;
    std::vector<std::shared_ptr<Comment>> comments;
    std::vector<std::shared_ptr<Attribute>> attributes;
    std::vector<std::string> errors;

    BaseNode() = default;
    BaseNode(SourceLocation loc) : location(std::move(loc)) {}
    BaseNode(SourceLocation loc,
             const std::vector<std::shared_ptr<Comment>>& comments,
             const std::vector<std::shared_ptr<Attribute>>& attributes,
             const std::vector<std::string>& errors)
        : location(std::move(loc)), comments(comments), attributes(attributes), errors(errors) {}
};

struct AttributeParam {
    std::unique_ptr<Expression> value;
    std::vector<std::shared_ptr<Comment>> comma;
};

struct Attribute {
    std::string name;
    std::vector<std::shared_ptr<AttributeParam>> params;
    Attribute() = default;
    Attribute(std::string name, const std::vector<std::shared_ptr<AttributeParam>>& params)
        : name(std::move(name)), params(params) {}
};

struct Package {
    std::string path;
    std::string package;
    std::vector<std::shared_ptr<File>> files;
    std::vector<std::shared_ptr<Statement>> body;
    std::vector<std::shared_ptr<Comment>> eof;
};

struct File {
    std::string name;
    std::string metadata;
    std::unique_ptr<PackageClause> package;
    std::vector<std::shared_ptr<ImportDeclaration>> imports;
    std::vector<std::shared_ptr<Statement>> body;
    std::vector<std::shared_ptr<Comment>> eof;
};

struct PackageClause {
    std::unique_ptr<Identifier> name;
    PackageClause() : name(nullptr) {}
    PackageClause(std::unique_ptr<Identifier> name) : name(std::move(name)) {}
};

struct ImportDeclaration {
    std::unique_ptr<Identifier> alias;
    std::unique_ptr<StringLit> path;
    ImportDeclaration() : alias(nullptr), path(nullptr) {}
    ImportDeclaration(std::unique_ptr<Identifier> alias, std::unique_ptr<StringLit> path)
        : alias(std::move(alias)), path(std::move(path)) {}
};

// stmt
struct ExprStmt {
    std::unique_ptr<Expression> expression;
    ExprStmt() = default;
    ExprStmt(std::unique_ptr<Expression> expr) : expression(std::move(expr)) {}
};

struct VariableAssgn {
    std::unique_ptr<Identifier> id;
    std::unique_ptr<Expression> init;
    VariableAssgn() = default;
    VariableAssgn(std::unique_ptr<Identifier> id, std::unique_ptr<Expression> init)
        : id(std::move(id)), init(std::move(init)) {}
};

struct OptionStmt {
    std::unique_ptr<Assignment> assignment;
    OptionStmt() = default;
    OptionStmt(std::unique_ptr<Assignment> assignment) : assignment(std::move(assignment)) {}
};

struct ReturnStmt {
    std::unique_ptr<Expression> argument;
    ReturnStmt() = default;
    ReturnStmt(std::unique_ptr<Expression> argument) : argument(std::move(argument)) {}
};

struct BadStmt {
    std::string text;
    BadStmt() = default;
    BadStmt(std::string text) : text(std::move(text)) {}
};

struct TestCaseStmt {
    std::unique_ptr<Identifier> id;
    std::unique_ptr<StringLit> extends;
    std::unique_ptr<Block> block;
    TestCaseStmt() = default;
    TestCaseStmt(std::unique_ptr<Identifier> id,
                 std::unique_ptr<StringLit> extends,
                 std::unique_ptr<Block> block)
        : id(std::move(id)), extends(std::move(extends)), block(std::move(block)) {}
};

struct BuiltinStmt {
    std::vector<std::shared_ptr<Comment>> colon;
    std::unique_ptr<Identifier> id;
    std::unique_ptr<TypeExpression> ty;
    BuiltinStmt() = default;
    BuiltinStmt(const std::vector<std::shared_ptr<Comment>>& colon,
                std::unique_ptr<Identifier> id,
                std::unique_ptr<TypeExpression> ty)
        : colon(colon), id(std::move(id)), ty(std::move(ty)) {}
};

struct Statement {
    enum class Type {
        ExpressionStatement,
        VariableAssignment,
        OptionStatement,
        ReturnStatement,
        BadStatement,
        TestCaseStatement,
        BuiltinStatement
    };
    Type type;

    using StmtVari = std::variant<std::unique_ptr<ExprStmt>,
                                  std::unique_ptr<VariableAssgn>,
                                  std::unique_ptr<OptionStmt>,
                                  std::unique_ptr<ReturnStmt>,
                                  std::unique_ptr<BadStmt>,
                                  std::unique_ptr<TestCaseStmt>,
                                  std::unique_ptr<BuiltinStmt>>;
    StmtVari stmt;

    Statement() = default;
    Statement(Type type, StmtVari stmt) : type(type), stmt(std::move(stmt)) {}

    std::shared_ptr<BaseNode> base() { return nullptr; }
};

// expr

struct Identifier {
    std::string name;
    Identifier() = default;
    Identifier(std::string name) : name(std::move(name)) {}
};

struct ArrayItem {
    std::unique_ptr<Expression> expression;
    std::vector<std::shared_ptr<Comment>> comma;
    ArrayItem() = default;
    ArrayItem(std::unique_ptr<Expression> expression,
              const std::vector<std::shared_ptr<Comment>>& comma)
        : expression(std::move(expression)), comma(comma) {}
};

struct ArrayExpr {
    std::vector<std::shared_ptr<Comment>> lbrack;
    std::vector<std::shared_ptr<ArrayItem>> elements;
    std::vector<std::shared_ptr<Comment>> rbrack;
    ArrayExpr() = default;
    ArrayExpr(const std::vector<std::shared_ptr<Comment>>& lbrack,
              const std::vector<std::shared_ptr<ArrayItem>>& elements,
              const std::vector<std::shared_ptr<Comment>>& rbrack)
        : lbrack(lbrack), elements(elements), rbrack(rbrack) {}
};

struct DictItem {
    std::unique_ptr<Expression> key;
    std::unique_ptr<Expression> val;
    std::vector<std::shared_ptr<Comment>> comma;
    DictItem() = default;
    DictItem(std::unique_ptr<Expression> key,
             std::unique_ptr<Expression> val,
             const std::vector<std::shared_ptr<Comment>>& comma)
        : key(std::move(key)), val(std::move(val)), comma(comma) {}
};

struct DictExpr {
    std::vector<std::shared_ptr<Comment>> lbrack;
    std::vector<std::shared_ptr<DictItem>> elements;
    std::vector<std::shared_ptr<Comment>> rbrack;
    DictExpr() = default;
    DictExpr(const std::vector<std::shared_ptr<Comment>>& lbrack,
             const std::vector<std::shared_ptr<DictItem>>& elements,
             const std::vector<std::shared_ptr<Comment>>& rbrack)
        : lbrack(lbrack), elements(elements), rbrack(rbrack) {}
};

struct FunctionExpr {
    std::vector<std::shared_ptr<Comment>> lparen;
    std::vector<std::shared_ptr<Property>> params;
    std::vector<std::shared_ptr<Comment>> rparen;
    std::vector<std::shared_ptr<Comment>> arrow;
    std::unique_ptr<FunctionBody> body;

    FunctionExpr() = default;
    FunctionExpr(const std::vector<std::shared_ptr<Comment>>& lparen,
                 const std::vector<std::shared_ptr<Property>>& params,
                 const std::vector<std::shared_ptr<Comment>>& rparen,
                 const std::vector<std::shared_ptr<Comment>>& arrow,
                 std::unique_ptr<FunctionBody> body)
        : lparen(lparen), params(params), rparen(rparen), arrow(arrow), body(std::move(body)) {}
};

struct LogicalExpr {
    LogicalOperator op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    LogicalExpr() = default;
    LogicalExpr(LogicalOperator op,
                std::unique_ptr<Expression> left,
                std::unique_ptr<Expression> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
};

struct WithSource {
    std::unique_ptr<Identifier> source;
    std::vector<std::shared_ptr<Comment>> with;
};

struct ObjectExpr {
    std::vector<std::shared_ptr<Comment>> lbrace;
    std::unique_ptr<WithSource> with;
    std::vector<std::shared_ptr<Property>> properties;
    std::vector<std::shared_ptr<Comment>> rbrace;
    ObjectExpr() = default;
    ObjectExpr(const std::vector<std::shared_ptr<Comment>>& lbrace,
               std::unique_ptr<WithSource> with,
               const std::vector<std::shared_ptr<Property>>& properties,
               const std::vector<std::shared_ptr<Comment>>& rbrace)
        : lbrace(lbrace), with(std::move(with)), properties(properties), rbrace(rbrace) {}
};

struct MemberExpr {
    std::unique_ptr<Expression> object;
    std::vector<std::shared_ptr<Comment>> lbrack;
    std::unique_ptr<PropertyKey> property;
    std::vector<std::shared_ptr<Comment>> rbrack;
    MemberExpr() = default;
    MemberExpr(std::unique_ptr<Expression> expr,
               const std::vector<std::shared_ptr<Comment>>& lbrack,
               std::unique_ptr<PropertyKey> property,
               const std::vector<std::shared_ptr<Comment>>& rbrack)
        : object(std::move(expr)), lbrack(lbrack), property(std::move(property)), rbrack(rbrack) {}
};

struct IndexExpr {
    std::unique_ptr<Expression> array;
    std::vector<std::shared_ptr<Comment>> lbrack;
    std::unique_ptr<Expression> index;
    std::vector<std::shared_ptr<Comment>> rbrack;

    IndexExpr() = default;
    IndexExpr(std::unique_ptr<Expression> array,
              const std::vector<std::shared_ptr<Comment>>& lbrack,
              std::unique_ptr<Expression> index,
              const std::vector<std::shared_ptr<Comment>>& rbrack)
        : array(std::move(array)), lbrack(lbrack), index(std::move(index)), rbrack(rbrack) {}
};

struct BinaryExpr {
    Operator op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    BinaryExpr() = default;
    BinaryExpr(Operator op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
};

struct UnaryExpr {
    Operator op;
    std::unique_ptr<Expression> argument;
    UnaryExpr() = default;
    UnaryExpr(Operator op, std::unique_ptr<Expression> argument)
        : op(op), argument(std::move(argument)) {}
};

struct PipeExpr {
    std::unique_ptr<Expression> argument;
    std::unique_ptr<CallExpr> call;
    PipeExpr() = default;
    PipeExpr(std::unique_ptr<Expression> argument, std::unique_ptr<CallExpr> call)
        : argument(std::move(argument)), call(std::move(call)) {}
};

struct CallExpr {
    std::unique_ptr<Expression> callee;
    std::vector<std::shared_ptr<Comment>> lparen;
    std::vector<std::shared_ptr<Expression>> arguments;
    std::vector<std::shared_ptr<Comment>> rparen;
    CallExpr() = default;
    CallExpr(std::unique_ptr<Expression> callee,
             const std::vector<std::shared_ptr<Comment>>& lparen,
             const std::vector<std::shared_ptr<Expression>>& arguments,
             const std::vector<std::shared_ptr<Comment>>& rparen)
        : callee(std::move(callee)), lparen(lparen), arguments(arguments), rparen(rparen) {}
};

struct ConditionalExpr {
    std::vector<std::shared_ptr<Comment>> tk_if;
    std::unique_ptr<Expression> test;
    std::vector<std::shared_ptr<Comment>> tk_then;
    std::unique_ptr<Expression> consequent;
    std::vector<std::shared_ptr<Comment>> tk_else;
    std::unique_ptr<Expression> alternate;
};

struct StringExpr {
    std::vector<std::shared_ptr<StringExprPart>> parts;
};

struct StringExprPart {
    enum class Type {
        Text,
        Interpolated,
    };
    using StringExprType =
        std::variant<std::unique_ptr<TextPart>, std::unique_ptr<InterpolatedPart>>;

    Type type;
    StringExprType part;
    StringExprPart() = default;
    StringExprPart(Type type, StringExprType part) : type(type), part(std::move(part)) {}
};

struct TextPart {
    std::string value;
};

struct InterpolatedPart {
    std::unique_ptr<Expression> expression;
    InterpolatedPart() = default;
    InterpolatedPart(std::unique_ptr<Expression> expression) : expression(std::move(expression)) {}
};

struct ParenExpr {
    std::vector<std::shared_ptr<Comment>> lparen;
    std::unique_ptr<Expression> expression;
    std::vector<std::shared_ptr<Comment>> rparen;
    ParenExpr() = default;
    ParenExpr(const std::vector<std::shared_ptr<Comment>>& lparen,
              std::unique_ptr<Expression> expr,
              const std::vector<std::shared_ptr<Comment>>& rparen)
        : lparen(lparen), expression(std::move(expr)), rparen(rparen) {}
};

struct IntegerLit {
    int64_t value;
    IntegerLit() = default;
    IntegerLit(int64_t value) : value(value) {}
};

struct FloatLit {
    double value;
    FloatLit() = default;
    FloatLit(double value) : value(value) {}
};

struct StringLit {
    std::string value;
    StringLit() = default;
    StringLit(std::string value) : value(std::move(value)) {}
};

struct DurationLit {
    std::vector<std::shared_ptr<Duration>> values;
    DurationLit() = default;
    DurationLit(const std::vector<std::shared_ptr<Duration>>& values) : values(values) {}
};

struct UintLit {
    uint64_t value;
    UintLit() : value(0) {}
    UintLit(uint64_t value) : value(value) {}
};

struct BooleanLit {
    bool value;
    BooleanLit() : value(false) {}
    BooleanLit(bool value) : value(value) {}
};

struct DateTimeLit {
    std::tm value;
    DateTimeLit() : value({}) {}
    DateTimeLit(const std::tm& value) : value(value) {}
};

struct RegexpLit {
    std::string value;
    RegexpLit() = default;
    RegexpLit(std::string value) : value(std::move(value)) {}
};

struct PipeLit {};

struct LabelLit {
    std::string value;
    LabelLit() = default;
    LabelLit(std::string value) : value(std::move(value)) {}
};

struct BadExpr {
    std::string text;
    std::unique_ptr<Expression> expression;
    BadExpr() = default;
    BadExpr(std::string text, std::unique_ptr<Expression> expression)
        : text(std::move(text)), expression(std::move(expression)) {}
};

struct Expression {
    enum class Type {
        Identifier,
        ArrayExpr,
        DictExpr,
        FunctionExpr,
        LogicalExpr,
        ObjectExpr,
        MemberExpr,
        IndexExpr,
        BinaryExpr,
        UnaryExpr,
        PipeExpr,
        CallExpr,
        ConditionalExpr,
        StringExpr,
        ParenExpr,
        IntegerLit,
        FloatLit,
        StringLit,
        DurationLit,
        UnsignedIntegerLit,
        BooleanLit,
        DateTimeLit,
        RegexpLit,
        PipeLit,
        LabelLit,
        BadExpr
    };
    Type type;

    using ExprType = std::variant<std::unique_ptr<Identifier>,
                                  std::unique_ptr<ArrayExpr>,
                                  std::unique_ptr<DictExpr>,
                                  std::unique_ptr<FunctionExpr>,
                                  std::unique_ptr<LogicalExpr>,
                                  std::unique_ptr<ObjectExpr>,
                                  std::unique_ptr<MemberExpr>,
                                  std::unique_ptr<IndexExpr>,
                                  std::unique_ptr<BinaryExpr>,
                                  std::unique_ptr<UnaryExpr>,
                                  std::unique_ptr<PipeExpr>,
                                  std::unique_ptr<CallExpr>,
                                  std::unique_ptr<ConditionalExpr>,
                                  std::unique_ptr<StringExpr>,
                                  std::unique_ptr<ParenExpr>,
                                  std::unique_ptr<IntegerLit>,
                                  std::unique_ptr<FloatLit>,
                                  std::unique_ptr<StringLit>,
                                  std::unique_ptr<DurationLit>,
                                  std::unique_ptr<UintLit>,
                                  std::unique_ptr<BooleanLit>,
                                  std::unique_ptr<DateTimeLit>,
                                  std::unique_ptr<RegexpLit>,
                                  std::unique_ptr<PipeLit>,
                                  std::unique_ptr<LabelLit>,
                                  std::unique_ptr<BadExpr>>;
    ExprType expr;
    Expression() = default;
    Expression(Type t, ExprType expr) : type(t), expr(std::move(expr)) {}
};

// operator
enum class Operator {
    MultiplicationOperator,
    DivisionOperator,
    ModuloOperator,
    PowerOperator,
    AdditionOperator,
    SubtractionOperator,
    LessThanEqualOperator,
    LessThanOperator,
    GreaterThanEqualOperator,
    GreaterThanOperator,
    StartsWithOperator,
    InOperator,
    NotOperator,
    ExistsOperator,
    NotEmptyOperator,
    EmptyOperator,
    EqualOperator,
    NotEqualOperator,
    RegexpMatchOperator,
    NotRegexpMatchOperator,
    InvalidOperator,
};

static std::unordered_map<std::string, Operator> operator_map = {
    {"*", Operator::MultiplicationOperator},
    {"/", Operator::DivisionOperator},
    {"%", Operator::ModuloOperator},
    {"^", Operator::PowerOperator},
    {"+", Operator::AdditionOperator},
    {"-", Operator::SubtractionOperator},
    {"<=", Operator::LessThanEqualOperator},
    {"<", Operator::LessThanOperator},
    {">=", Operator::GreaterThanEqualOperator},
    {">", Operator::GreaterThanOperator},
    {"startswith", Operator::StartsWithOperator},
    {"in", Operator::InOperator},
    {"not", Operator::NotOperator},
    {"exists", Operator::ExistsOperator},
    {"not empty", Operator::NotEmptyOperator},
    {"empty", Operator::EmptyOperator},
    {"==", Operator::EqualOperator},
    {"!=", Operator::NotEqualOperator},
    {"=~", Operator::RegexpMatchOperator},
    {"!~", Operator::NotRegexpMatchOperator},
    {"<INVALID_OP>", Operator::InvalidOperator},
};

inline std::string operator_to_string(Operator op) {
    switch (op) {
    case Operator::MultiplicationOperator:
        return "MultiplicationOperator";
    case Operator::DivisionOperator:
        return "DivisionOperator";
    case Operator::ModuloOperator:
        return "ModuloOperator";
    case Operator::PowerOperator:
        return "PowerOperator";
    case Operator::AdditionOperator:
        return "AdditionOperator";
    case Operator::SubtractionOperator:
        return "SubtractionOperator";
    case Operator::LessThanEqualOperator:
        return "LessThanEqualOperator";
    case Operator::LessThanOperator:
        return "LessThanOperator";
    case Operator::GreaterThanEqualOperator:
        return "GreaterThanEqualOperator";
    case Operator::GreaterThanOperator:
        return "GreaterThanOperator";
    case Operator::StartsWithOperator:
        return "StartsWithOperator";
    case Operator::InOperator:
        return "InOperator";
    case Operator::NotOperator:
        return "NotOperator";
    case Operator::ExistsOperator:
        return "ExistsOperator";
    case Operator::NotEmptyOperator:
        return "NotEmptyOperator";
    case Operator::EmptyOperator:
        return "EmptyOperator";
    case Operator::EqualOperator:
        return "EqualOperator";
    case Operator::NotEqualOperator:
        return "NotEqualOperator";
    case Operator::RegexpMatchOperator:
        return "RegexpMatchOperator";
    case Operator::NotRegexpMatchOperator:
        return "NotRegexpMatchOperator";
    case Operator::InvalidOperator:
        return "InvalidOperator";
    }
}

enum class LogicalOperator {
    AndOperator,
    OrOperator,
};

// assign
struct MemberAssgn {
    std::unique_ptr<MemberExpr> member;
    std::unique_ptr<Expression> init;
    MemberAssgn() = default;
    MemberAssgn(std::unique_ptr<MemberExpr> member, std::unique_ptr<Expression> init)
        : member(std::move(member)), init(std::move(init)) {}
};

struct Assignment {
    using AssiType = std::variant<std::unique_ptr<VariableAssgn>, std::unique_ptr<MemberAssgn>>;
    enum class Type { VariableAssignment, MemberAssignment };
    Type type;
    AssiType value;

    Assignment() = default;
    Assignment(Assignment::Type type, AssiType value) : type(type), value(std::move(value)) {}
};

// property

struct Property {
    std::unique_ptr<PropertyKey> key;
    std::vector<std::shared_ptr<Comment>> separator;
    std::unique_ptr<Expression> value;
    std::vector<std::shared_ptr<Comment>> comma;
    Property() = default;
    Property(std::unique_ptr<PropertyKey> key,
             const std::vector<std::shared_ptr<Comment>>& separator,
             std::unique_ptr<Expression> value,
             const std::vector<std::shared_ptr<Comment>>& comma)
        : key(std::move(key)), separator(separator), value(std::move(value)), comma(comma) {}
};

struct PropertyKey {
    using PropKeyType = std::variant<std::shared_ptr<Identifier>, std::shared_ptr<StringLit>>;
    enum class Type { Identifier, StringLiteral };

    Type type;
    PropKeyType key;

    PropertyKey() = default;
    PropertyKey(PropertyKey::Type type, PropKeyType key) : type(type), key(std::move(key)) {}
};

// function

struct Block {
    std::vector<std::shared_ptr<Comment>> lbrace;
    std::vector<std::shared_ptr<Statement>> body;
    std::vector<std::shared_ptr<Comment>> rbrace;

    Block() = default;
    Block(const std::vector<std::shared_ptr<Comment>>& lbrace,
          const std::vector<std::shared_ptr<Statement>>& body,
          const std::vector<std::shared_ptr<Comment>>& rbrace)
        : lbrace(lbrace), body(body), rbrace(rbrace) {}
};

struct FunctionBody {
    enum class Type { Block, Expression };
    using FuncType = std::variant<std::shared_ptr<Block>, std::shared_ptr<Expression>>;
    Type type;
    FuncType body;
    FunctionBody(Type t, FuncType body) : type(t), body(std::move(body)) {}
};

// parameter

struct TvarType {
    std::unique_ptr<Identifier> name;
    TvarType() = default;
    TvarType(std::unique_ptr<Identifier> name) : name(std::move(name)) {}
};

struct NamedType {
    std::unique_ptr<Identifier> name;
    NamedType() = default;
    NamedType(std::unique_ptr<Identifier> name) : name(std::move(name)) {}
};

struct ArrayType {
    std::unique_ptr<MonoType> element;
    ArrayType() = default;
    ArrayType(std::unique_ptr<MonoType> element) : element(std::move(element)) {}
};

struct StreamType {
    std::unique_ptr<MonoType> element;
    StreamType() = default;
    StreamType(std::unique_ptr<MonoType> element) : element(std::move(element)) {}
};

struct VectorType {
    std::unique_ptr<MonoType> element;
    VectorType() = default;
    VectorType(std::unique_ptr<MonoType> element) : element(std::move(element)) {}
};

struct DictType {
    std::unique_ptr<MonoType> key;
    std::unique_ptr<MonoType> val;
    DictType() = default;
    DictType(std::unique_ptr<MonoType> key, std::unique_ptr<MonoType> val)
        : key(std::move(key)), val(std::move(val)) {}
};

struct DynamicType {};

struct FunctionType {
    std::vector<std::shared_ptr<ParameterType>> parameters;
    std::unique_ptr<MonoType> monotype;
};

struct RecordType {
    std::unique_ptr<Identifier> tvar;
    std::vector<std::shared_ptr<PropertyType>> properties;
};

struct TypeExpression {
    std::unique_ptr<MonoType> monotype;
    std::vector<std::shared_ptr<TypeConstraint>> constraints;
    TypeExpression() = default;
    TypeExpression(std::unique_ptr<MonoType> monotype,
                   const std::vector<std::shared_ptr<TypeConstraint>>& constraints)
        : monotype(std::move(monotype)), constraints(constraints) {}
};

struct TypeConstraint {
    std::unique_ptr<Identifier> tvar;
    std::vector<std::shared_ptr<Identifier>> kinds;
    TypeConstraint() = default;
    TypeConstraint(std::unique_ptr<Identifier> tvar,
                   const std::vector<std::shared_ptr<Identifier>>& kinds)
        : tvar(std::move(tvar)), kinds(kinds) {}
};

struct MonoType {
    enum class Type {
        Tvar,
        Basic,
        Array,
        Stream,
        Vector,
        Dict,
        Dynamic,
        Record,
        Function,
        Label,
    };

    using MonoVari = std::variant<std::unique_ptr<TvarType>,
                                  std::unique_ptr<NamedType>,
                                  std::unique_ptr<ArrayType>,
                                  std::unique_ptr<StreamType>,
                                  std::unique_ptr<VectorType>,
                                  std::unique_ptr<DictType>,
                                  std::unique_ptr<DynamicType>,
                                  std::unique_ptr<RecordType>,
                                  std::unique_ptr<FunctionType>,
                                  std::unique_ptr<LabelLit>>;
    Type type;
    MonoVari value;

    MonoType() = default;
    MonoType(MonoType::Type type, MonoVari value) : type(type), value(std::move(value)) {}
};

struct Required {
    std::unique_ptr<Identifier> name;
    std::unique_ptr<MonoType> monotype;
};

struct Optional {
    std::unique_ptr<Identifier> name;
    std::unique_ptr<MonoType> monotype;
    std::unique_ptr<LabelLit> _default;
};

struct Pipe {
    std::unique_ptr<Identifier> name;
    std::unique_ptr<MonoType> monotype;
};

struct ParameterType {
    enum class Type {
        Required,
        Optional,
        Pipe,
    };

    using ParamType =
        std::variant<std::shared_ptr<Required>, std::shared_ptr<Optional>, std::shared_ptr<Pipe>>;

    Type type;
    ParamType value;

    ParameterType() = default;
    ParameterType(ParameterType::Type type, ParamType value)
        : type(type), value(std::move(value)) {}
};

} // namespace pl