/*!
 * Copyright (c) 2021 Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for
 * license information.
 */
#pragma once

#ifndef FREEFORM2_EXPRESSION_H
#define FREEFORM2_EXPRESSION_H

#include <basic_types.h>

#include <boost/noncopyable.hpp>
#include <ostream>

#include "FreeForm2.h"
#include "FreeForm2Executable.h"
#include "FreeForm2Result.h"
#include "TypeImpl.h"

namespace DynamicRank {
class IFeatureMap;
}

namespace FreeForm2 {
class Visitor;

// This structure represents a strongly-typed identifier for variable
// bindings.
struct VariableID {
  unsigned int m_value;

  // Comparison operators for IDs.
  bool operator==(VariableID p_other) const;
  bool operator!=(VariableID p_other) const;
  bool operator<(VariableID p_other) const;

  static const VariableID c_invalidID;
};

// Stream insertion operator for VariableIDs.
template <typename CharType, typename CharTraits>
std::basic_ostream<CharType, CharTraits> &operator<<(
    std::basic_ostream<CharType, CharTraits> &p_out, VariableID p_id) {
  return p_out << p_id.m_value;
}

// Class that owns expressions generated by an Expression::Parse.
class ExpressionOwner : boost::noncopyable {
 public:
  virtual ~ExpressionOwner() = 0;
};

// A struct that holds the static range of valid values for an expression.
struct ValueBounds {
  ValueBounds();
  ValueBounds(const TypeImpl &p_type);
  ValueBounds(const TypeImpl &p_type, ConstantValue p_value);
  ValueBounds(Result::IntType p_lower, Result::IntType p_upper);

  bool operator==(const ValueBounds &p_other) const;
  bool operator!=(const ValueBounds &p_other) const;

  Result::IntType m_lower;
  Result::IntType m_upper;

  // An empty range, defined in such a way that the Union and Intersection
  // operators are well defined.
  static const ValueBounds c_empty;
};

// A struct that holds all the annotations for an expression node.
struct Annotations {
  Annotations();
  Annotations(SourceLocation p_sourceLocation);
  Annotations(SourceLocation p_sourceLocation, ValueBounds p_valueBounds);

  ValueBounds m_valueBounds;
  SourceLocation m_sourceLocation;
};

// Expression class, that can be used to evaluate free form2 expressions.
class Expression : boost::noncopyable {
 public:
  typedef Executable::FeatureType FeatureType;

  typedef Executable::InputType InputType;

  explicit Expression(const Annotations &p_annotations);

  virtual ~Expression();

  // Invoke the visitor pattern over the expression tree.
  virtual void Accept(Visitor &) const = 0;

  // Invoke the visitor pattern over the expression tree, with the added
  // caveat that the visitor is expected to produce a reference instead of
  // a value.
  virtual void AcceptReference(Visitor &) const;

  // Returns the type of this expression.
  virtual const TypeImpl &GetType() const = 0;

  // Returns the number of children of this expression.
  virtual size_t GetNumChildren() const = 0;

  // Returns a flag indicating whether or not this expression is a
  // compile-time constant.
  virtual bool IsConstant() const;

  // Retrieve the value of this expression as a compile-time constant.
  // The member of Literal used is determined by the type of the
  // Expression. If this expression is not a compile-time constant, this
  // method throws an exception.
  virtual ConstantValue GetConstantValue() const;

  // Gets the annotations for the current node.
  const Annotations &GetAnnotations() const;

  // Retrieve the compile-time inferred interval of possible values for this
  // expression. This information is calculated from the type of the expression,
  // constants, binary operations and foreach loops. Since this is a
  // compile-time assertion, many expressions won't be able to correctly
  // determine the bounds and instead will return a default value of
  // (std::numeric_limits<type>::min(), std::numeric_limits<type>::max()).
  virtual const ValueBounds &GetValueBounds() const;

  // Retrieve the source code location for this particular expression.
  virtual const SourceLocation &GetSourceLocation() const;

 protected:
  // The annotations (assertions and source location) for this expression node.
  const Annotations m_annotations;
};
}  // namespace FreeForm2

#endif
