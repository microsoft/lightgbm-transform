/*!
 * Copyright (c) 2021 Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for
 * license information.
 */

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Tool     : bondc, Version=3.0.1, Build=bond-git.retail.0
//     Template : Microsoft.Bond.Rules.dll#Rules_BOND_CPP.tt
//     File     : NeuralInput_types.h
//
//     Changes to this file may cause incorrect behavior and will be lost when
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

#pragma once

#include <bond/core/bond_version.h>
#if BOND_MAJOR_VERSION_MIN_SUPPORTED > 3 ||   \
    (BOND_MAJOR_VERSION_MIN_SUPPORTED == 3 && \
     BOND_MINOR_VERSION_MIN_SUPPORTED > 1)
#error This file was generated by an older Bond compiler which is \
       incompatible with current Bond library. Please regenerate \
       with the latest Bond compiler.
#endif

#include <bond/core/config.h>
#include <bond/core/containers.h>
#include <bond/core/nullable.h>

namespace DynamicRank {

// NeuralInputBondData
struct NeuralInputBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional nullable<vector<string>> m_segments
  bond::nullable<std::vector<std::string> > m_segments;

  NeuralInputBondData() {
    InitMetadata("NeuralInputBondData", "DynamicRank.NeuralInputBondData");
  }

  NeuralInputBondData(const NeuralInputBondData &_bond_rhs)
      : name(_bond_rhs.name.get_allocator()), m_segments(_bond_rhs.m_segments) {
    InitMetadata("NeuralInputBondData", "DynamicRank.NeuralInputBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputBondData(NeuralInputBondData &&_bond_rhs) BOND_NOEXCEPT_IF(
      (true && std::is_nothrow_move_constructible<std::string>::value &&
       std::is_nothrow_move_constructible<
           bond::nullable<std::vector<std::string> > >::value))
      : name(std::move(_bond_rhs.name)),
        m_segments(std::move(_bond_rhs.m_segments)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputBondData(Allocator *_bond_allocator)
      : name(*_bond_allocator), m_segments(*_bond_allocator) {
    InitMetadata("NeuralInputBondData", "DynamicRank.NeuralInputBondData");
  }

  NeuralInputBondData &operator=(const NeuralInputBondData &_bond_rhs) {
    NeuralInputBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputBondData &operator=(NeuralInputBondData &&_bond_rhs) {
    NeuralInputBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputBondData &_bond_other) const {
    return true
           // skip bond_meta::full_name field 'name'
           && (m_segments == _bond_other.m_segments);
  }

  bool operator!=(const NeuralInputBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputBondData &_bond_other) {
    using std::swap;
    // skip bond_meta::full_name field 'name'
    swap(m_segments, _bond_other.m_segments);
  }

  struct Schema;

 protected:
  void InitMetadata(const char * /*_bond_name*/, const char *_bond_full_name) {
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputBondData &_bond_left,
                 NeuralInputBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// BulkNeuralInputBondData
struct BulkNeuralInputBondData {
  // 1: optional vector<uint32> m_features
  std::vector<uint32_t> m_features;

  // 2: optional string m_code
  std::string m_code;

  // 3: optional uint32 m_input
  uint32_t m_input;

  BulkNeuralInputBondData() : m_input() {}

  // Compiler generated copy ctor OK
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
  BulkNeuralInputBondData(const BulkNeuralInputBondData & /*_bond_rhs*/) =
      default;
#endif

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  BulkNeuralInputBondData(BulkNeuralInputBondData &&_bond_rhs) BOND_NOEXCEPT_IF(
      (true &&
       std::is_nothrow_move_constructible<std::vector<uint32_t> >::value &&
       std::is_nothrow_move_constructible<std::string>::value &&
       std::is_nothrow_move_constructible<uint32_t>::value))
      : m_features(std::move(_bond_rhs.m_features)),
        m_code(std::move(_bond_rhs.m_code)),
        m_input(std::move(_bond_rhs.m_input)) {}
#endif

  template <typename Allocator>
  explicit BulkNeuralInputBondData(Allocator *_bond_allocator)
      : m_features(*_bond_allocator), m_code(*_bond_allocator), m_input() {}

  // Compiler generated operator= OK
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
  BulkNeuralInputBondData &operator=(const BulkNeuralInputBondData &_bond_rhs) =
      default;
#endif

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  BulkNeuralInputBondData &operator=(BulkNeuralInputBondData &&_bond_rhs) {
    BulkNeuralInputBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const BulkNeuralInputBondData &_bond_other) const {
    return true && (m_features == _bond_other.m_features) &&
           (m_code == _bond_other.m_code) && (m_input == _bond_other.m_input);
  }

  bool operator!=(const BulkNeuralInputBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(BulkNeuralInputBondData &_bond_other) {
    using std::swap;
    swap(m_features, _bond_other.m_features);
    swap(m_code, _bond_other.m_code);
    swap(m_input, _bond_other.m_input);
  }

  struct Schema;

 protected:
  void InitMetadata(const char * /*_bond_name*/,
                    const char * /*_bond_full_name*/) {}
};

inline void swap(BulkNeuralInputBondData &_bond_left,
                 BulkNeuralInputBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputUnaryBondData
struct NeuralInputUnaryBondData : public ::DynamicRank::NeuralInputBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional uint32 m_iFeature
  uint32_t m_iFeature;

  NeuralInputUnaryBondData() : m_iFeature() {
    InitMetadata("NeuralInputUnaryBondData",
                 "DynamicRank.NeuralInputUnaryBondData");
  }

  NeuralInputUnaryBondData(const NeuralInputUnaryBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_iFeature(_bond_rhs.m_iFeature) {
    InitMetadata("NeuralInputUnaryBondData",
                 "DynamicRank.NeuralInputUnaryBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputUnaryBondData(NeuralInputUnaryBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true &&
           std::is_nothrow_move_constructible<
               ::DynamicRank::NeuralInputBondData>::value &&
           std::is_nothrow_move_constructible<std::string>::value &&
           std::is_nothrow_move_constructible<uint32_t>::value))
      : ::DynamicRank::NeuralInputBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_iFeature(std::move(_bond_rhs.m_iFeature)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputUnaryBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputBondData(_bond_allocator),
        name(*_bond_allocator),
        m_iFeature() {
    InitMetadata("NeuralInputUnaryBondData",
                 "DynamicRank.NeuralInputUnaryBondData");
  }

  NeuralInputUnaryBondData &operator=(
      const NeuralInputUnaryBondData &_bond_rhs) {
    NeuralInputUnaryBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputUnaryBondData &operator=(NeuralInputUnaryBondData &&_bond_rhs) {
    NeuralInputUnaryBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputUnaryBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputBondData &>(*this) ==
            static_cast<const ::DynamicRank::NeuralInputBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_iFeature == _bond_other.m_iFeature);
  }

  bool operator!=(const NeuralInputUnaryBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputUnaryBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_iFeature, _bond_other.m_iFeature);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputBondData::InitMetadata(_bond_name,
                                                     _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputUnaryBondData &_bond_left,
                 NeuralInputUnaryBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputLinearBondData
struct NeuralInputLinearBondData
    : public ::DynamicRank::NeuralInputUnaryBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional double m_slope
  double m_slope;

  // 3: optional double m_intercept
  double m_intercept;

  NeuralInputLinearBondData() : m_slope(), m_intercept() {
    InitMetadata("NeuralInputLinearBondData",
                 "DynamicRank.NeuralInputLinearBondData");
  }

  NeuralInputLinearBondData(const NeuralInputLinearBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_slope(_bond_rhs.m_slope),
        m_intercept(_bond_rhs.m_intercept) {
    InitMetadata("NeuralInputLinearBondData",
                 "DynamicRank.NeuralInputLinearBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputLinearBondData(NeuralInputLinearBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true &&
           std::is_nothrow_move_constructible<
               ::DynamicRank::NeuralInputUnaryBondData>::value &&
           std::is_nothrow_move_constructible<std::string>::value &&
           std::is_nothrow_move_constructible<double>::value))
      : ::DynamicRank::NeuralInputUnaryBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_slope(std::move(_bond_rhs.m_slope)),
        m_intercept(std::move(_bond_rhs.m_intercept)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputLinearBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_allocator),
        name(*_bond_allocator),
        m_slope(),
        m_intercept() {
    InitMetadata("NeuralInputLinearBondData",
                 "DynamicRank.NeuralInputLinearBondData");
  }

  NeuralInputLinearBondData &operator=(
      const NeuralInputLinearBondData &_bond_rhs) {
    NeuralInputLinearBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputLinearBondData &operator=(NeuralInputLinearBondData &&_bond_rhs) {
    NeuralInputLinearBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputLinearBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_slope == _bond_other.m_slope) &&
           (m_intercept == _bond_other.m_intercept);
  }

  bool operator!=(const NeuralInputLinearBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputLinearBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputUnaryBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_slope, _bond_other.m_slope);
    swap(m_intercept, _bond_other.m_intercept);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputUnaryBondData::InitMetadata(_bond_name,
                                                          _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputLinearBondData &_bond_left,
                 NeuralInputLinearBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputLogLinearBondData
struct NeuralInputLogLinearBondData
    : public ::DynamicRank::NeuralInputLinearBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  NeuralInputLogLinearBondData() {
    InitMetadata("NeuralInputLogLinearBondData",
                 "DynamicRank.NeuralInputLogLinearBondData");
  }

  NeuralInputLogLinearBondData(const NeuralInputLogLinearBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputLinearBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()) {
    InitMetadata("NeuralInputLogLinearBondData",
                 "DynamicRank.NeuralInputLogLinearBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputLogLinearBondData(NeuralInputLogLinearBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF((true &&
                        std::is_nothrow_move_constructible<
                            ::DynamicRank::NeuralInputLinearBondData>::value &&
                        std::is_nothrow_move_constructible<std::string>::value))
      : ::DynamicRank::NeuralInputLinearBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputLogLinearBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputLinearBondData(_bond_allocator),
        name(*_bond_allocator) {
    InitMetadata("NeuralInputLogLinearBondData",
                 "DynamicRank.NeuralInputLogLinearBondData");
  }

  NeuralInputLogLinearBondData &operator=(
      const NeuralInputLogLinearBondData &_bond_rhs) {
    NeuralInputLogLinearBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputLogLinearBondData &operator=(
      NeuralInputLogLinearBondData &&_bond_rhs) {
    NeuralInputLogLinearBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputLogLinearBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputLinearBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputLinearBondData &>(
                _bond_other));
    // skip bond_meta::full_name field 'name'
  }

  bool operator!=(const NeuralInputLogLinearBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputLogLinearBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputLinearBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputLinearBondData::InitMetadata(_bond_name,
                                                           _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputLogLinearBondData &_bond_left,
                 NeuralInputLogLinearBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputRationalBondData
struct NeuralInputRationalBondData
    : public ::DynamicRank::NeuralInputUnaryBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional double m_dblDampingFactor
  double m_dblDampingFactor;

  NeuralInputRationalBondData() : m_dblDampingFactor() {
    InitMetadata("NeuralInputRationalBondData",
                 "DynamicRank.NeuralInputRationalBondData");
  }

  NeuralInputRationalBondData(const NeuralInputRationalBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_dblDampingFactor(_bond_rhs.m_dblDampingFactor) {
    InitMetadata("NeuralInputRationalBondData",
                 "DynamicRank.NeuralInputRationalBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputRationalBondData(NeuralInputRationalBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true &&
           std::is_nothrow_move_constructible<
               ::DynamicRank::NeuralInputUnaryBondData>::value &&
           std::is_nothrow_move_constructible<std::string>::value &&
           std::is_nothrow_move_constructible<double>::value))
      : ::DynamicRank::NeuralInputUnaryBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_dblDampingFactor(std::move(_bond_rhs.m_dblDampingFactor)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputRationalBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_allocator),
        name(*_bond_allocator),
        m_dblDampingFactor() {
    InitMetadata("NeuralInputRationalBondData",
                 "DynamicRank.NeuralInputRationalBondData");
  }

  NeuralInputRationalBondData &operator=(
      const NeuralInputRationalBondData &_bond_rhs) {
    NeuralInputRationalBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputRationalBondData &operator=(
      NeuralInputRationalBondData &&_bond_rhs) {
    NeuralInputRationalBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputRationalBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_dblDampingFactor == _bond_other.m_dblDampingFactor);
  }

  bool operator!=(const NeuralInputRationalBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputRationalBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputUnaryBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_dblDampingFactor, _bond_other.m_dblDampingFactor);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputUnaryBondData::InitMetadata(_bond_name,
                                                          _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputRationalBondData &_bond_left,
                 NeuralInputRationalBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputBucketBondData
struct NeuralInputBucketBondData
    : public ::DynamicRank::NeuralInputUnaryBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional bool m_fMinInclusive
  bool m_fMinInclusive;

  // 3: optional bool m_fMaxInclusive
  bool m_fMaxInclusive;

  // 4: optional uint32 m_nMinValue
  uint32_t m_nMinValue;

  // 5: optional uint32 m_nMaxValue
  uint32_t m_nMaxValue;

  NeuralInputBucketBondData()
      : m_fMinInclusive(), m_fMaxInclusive(), m_nMinValue(), m_nMaxValue() {
    InitMetadata("NeuralInputBucketBondData",
                 "DynamicRank.NeuralInputBucketBondData");
  }

  NeuralInputBucketBondData(const NeuralInputBucketBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_fMinInclusive(_bond_rhs.m_fMinInclusive),
        m_fMaxInclusive(_bond_rhs.m_fMaxInclusive),
        m_nMinValue(_bond_rhs.m_nMinValue),
        m_nMaxValue(_bond_rhs.m_nMaxValue) {
    InitMetadata("NeuralInputBucketBondData",
                 "DynamicRank.NeuralInputBucketBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputBucketBondData(NeuralInputBucketBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true &&
           std::is_nothrow_move_constructible<
               ::DynamicRank::NeuralInputUnaryBondData>::value &&
           std::is_nothrow_move_constructible<std::string>::value &&
           std::is_nothrow_move_constructible<bool>::value &&
           std::is_nothrow_move_constructible<uint32_t>::value))
      : ::DynamicRank::NeuralInputUnaryBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_fMinInclusive(std::move(_bond_rhs.m_fMinInclusive)),
        m_fMaxInclusive(std::move(_bond_rhs.m_fMaxInclusive)),
        m_nMinValue(std::move(_bond_rhs.m_nMinValue)),
        m_nMaxValue(std::move(_bond_rhs.m_nMaxValue)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputBucketBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_allocator),
        name(*_bond_allocator),
        m_fMinInclusive(),
        m_fMaxInclusive(),
        m_nMinValue(),
        m_nMaxValue() {
    InitMetadata("NeuralInputBucketBondData",
                 "DynamicRank.NeuralInputBucketBondData");
  }

  NeuralInputBucketBondData &operator=(
      const NeuralInputBucketBondData &_bond_rhs) {
    NeuralInputBucketBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputBucketBondData &operator=(NeuralInputBucketBondData &&_bond_rhs) {
    NeuralInputBucketBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputBucketBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_fMinInclusive == _bond_other.m_fMinInclusive) &&
           (m_fMaxInclusive == _bond_other.m_fMaxInclusive) &&
           (m_nMinValue == _bond_other.m_nMinValue) &&
           (m_nMaxValue == _bond_other.m_nMaxValue);
  }

  bool operator!=(const NeuralInputBucketBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputBucketBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputUnaryBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_fMinInclusive, _bond_other.m_fMinInclusive);
    swap(m_fMaxInclusive, _bond_other.m_fMaxInclusive);
    swap(m_nMinValue, _bond_other.m_nMinValue);
    swap(m_nMaxValue, _bond_other.m_nMaxValue);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputUnaryBondData::InitMetadata(_bond_name,
                                                          _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputBucketBondData &_bond_left,
                 NeuralInputBucketBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputTanhBondData
struct NeuralInputTanhBondData : public ::DynamicRank::NeuralInputBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional uint32 m_cInputs
  uint32_t m_cInputs;

  // 3: optional bool m_locked
  bool m_locked;

  // 4: optional double m_threshold
  double m_threshold;

  // 5: optional vector<uint32> m_rgId
  std::vector<uint32_t> m_rgId;

  // 6: optional vector<double> m_rgWeights
  std::vector<double> m_rgWeights;

  NeuralInputTanhBondData() : m_cInputs(), m_locked(), m_threshold() {
    InitMetadata("NeuralInputTanhBondData",
                 "DynamicRank.NeuralInputTanhBondData");
  }

  NeuralInputTanhBondData(const NeuralInputTanhBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_cInputs(_bond_rhs.m_cInputs),
        m_locked(_bond_rhs.m_locked),
        m_threshold(_bond_rhs.m_threshold),
        m_rgId(_bond_rhs.m_rgId),
        m_rgWeights(_bond_rhs.m_rgWeights) {
    InitMetadata("NeuralInputTanhBondData",
                 "DynamicRank.NeuralInputTanhBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputTanhBondData(NeuralInputTanhBondData &&_bond_rhs) BOND_NOEXCEPT_IF(
      (true &&
       std::is_nothrow_move_constructible<
           ::DynamicRank::NeuralInputBondData>::value &&
       std::is_nothrow_move_constructible<std::string>::value &&
       std::is_nothrow_move_constructible<uint32_t>::value &&
       std::is_nothrow_move_constructible<bool>::value &&
       std::is_nothrow_move_constructible<double>::value &&
       std::is_nothrow_move_constructible<std::vector<uint32_t> >::value &&
       std::is_nothrow_move_constructible<std::vector<double> >::value))
      : ::DynamicRank::NeuralInputBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_cInputs(std::move(_bond_rhs.m_cInputs)),
        m_locked(std::move(_bond_rhs.m_locked)),
        m_threshold(std::move(_bond_rhs.m_threshold)),
        m_rgId(std::move(_bond_rhs.m_rgId)),
        m_rgWeights(std::move(_bond_rhs.m_rgWeights)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputTanhBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputBondData(_bond_allocator),
        name(*_bond_allocator),
        m_cInputs(),
        m_locked(),
        m_threshold(),
        m_rgId(*_bond_allocator),
        m_rgWeights(*_bond_allocator) {
    InitMetadata("NeuralInputTanhBondData",
                 "DynamicRank.NeuralInputTanhBondData");
  }

  NeuralInputTanhBondData &operator=(const NeuralInputTanhBondData &_bond_rhs) {
    NeuralInputTanhBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputTanhBondData &operator=(NeuralInputTanhBondData &&_bond_rhs) {
    NeuralInputTanhBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputTanhBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputBondData &>(*this) ==
            static_cast<const ::DynamicRank::NeuralInputBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_cInputs == _bond_other.m_cInputs) &&
           (m_locked == _bond_other.m_locked) &&
           (m_threshold == _bond_other.m_threshold) &&
           (m_rgId == _bond_other.m_rgId) &&
           (m_rgWeights == _bond_other.m_rgWeights);
  }

  bool operator!=(const NeuralInputTanhBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputTanhBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_cInputs, _bond_other.m_cInputs);
    swap(m_locked, _bond_other.m_locked);
    swap(m_threshold, _bond_other.m_threshold);
    swap(m_rgId, _bond_other.m_rgId);
    swap(m_rgWeights, _bond_other.m_rgWeights);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputBondData::InitMetadata(_bond_name,
                                                     _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputTanhBondData &_bond_left,
                 NeuralInputTanhBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputTanhUnaryBondData
struct NeuralInputTanhUnaryBondData
    : public ::DynamicRank::NeuralInputUnaryBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  // 2: optional bool m_fLocked
  bool m_fLocked;

  // 3: optional double m_dblWeights
  double m_dblWeights;

  // 4: optional double m_dblThreshold
  double m_dblThreshold;

  NeuralInputTanhUnaryBondData()
      : m_fLocked(), m_dblWeights(), m_dblThreshold() {
    InitMetadata("NeuralInputTanhUnaryBondData",
                 "DynamicRank.NeuralInputTanhUnaryBondData");
  }

  NeuralInputTanhUnaryBondData(const NeuralInputTanhUnaryBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()),
        m_fLocked(_bond_rhs.m_fLocked),
        m_dblWeights(_bond_rhs.m_dblWeights),
        m_dblThreshold(_bond_rhs.m_dblThreshold) {
    InitMetadata("NeuralInputTanhUnaryBondData",
                 "DynamicRank.NeuralInputTanhUnaryBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputTanhUnaryBondData(NeuralInputTanhUnaryBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true &&
           std::is_nothrow_move_constructible<
               ::DynamicRank::NeuralInputUnaryBondData>::value &&
           std::is_nothrow_move_constructible<std::string>::value &&
           std::is_nothrow_move_constructible<bool>::value &&
           std::is_nothrow_move_constructible<double>::value))
      : ::DynamicRank::NeuralInputUnaryBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)),
        m_fLocked(std::move(_bond_rhs.m_fLocked)),
        m_dblWeights(std::move(_bond_rhs.m_dblWeights)),
        m_dblThreshold(std::move(_bond_rhs.m_dblThreshold)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputTanhUnaryBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_allocator),
        name(*_bond_allocator),
        m_fLocked(),
        m_dblWeights(),
        m_dblThreshold() {
    InitMetadata("NeuralInputTanhUnaryBondData",
                 "DynamicRank.NeuralInputTanhUnaryBondData");
  }

  NeuralInputTanhUnaryBondData &operator=(
      const NeuralInputTanhUnaryBondData &_bond_rhs) {
    NeuralInputTanhUnaryBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputTanhUnaryBondData &operator=(
      NeuralInputTanhUnaryBondData &&_bond_rhs) {
    NeuralInputTanhUnaryBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputTanhUnaryBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                _bond_other))
           // skip bond_meta::full_name field 'name'
           && (m_fLocked == _bond_other.m_fLocked) &&
           (m_dblWeights == _bond_other.m_dblWeights) &&
           (m_dblThreshold == _bond_other.m_dblThreshold);
  }

  bool operator!=(const NeuralInputTanhUnaryBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputTanhUnaryBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputUnaryBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
    swap(m_fLocked, _bond_other.m_fLocked);
    swap(m_dblWeights, _bond_other.m_dblWeights);
    swap(m_dblThreshold, _bond_other.m_dblThreshold);
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputUnaryBondData::InitMetadata(_bond_name,
                                                          _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputTanhUnaryBondData &_bond_left,
                 NeuralInputTanhUnaryBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// UnionNeuralInputTanhBondData
struct UnionNeuralInputTanhBondData {
  // 1: optional bool m_cached
  bool m_cached;

  // 2: optional nullable<DynamicRank.NeuralInputTanhBondData>
  // m_neuralInputTanhBondData
  bond::nullable< ::DynamicRank::NeuralInputTanhBondData>
      m_neuralInputTanhBondData;

  // 3: optional nullable<DynamicRank.NeuralInputTanhUnaryBondData>
  // m_neuralInputTanhUnaryBondData
  bond::nullable< ::DynamicRank::NeuralInputTanhUnaryBondData>
      m_neuralInputTanhUnaryBondData;

  UnionNeuralInputTanhBondData() : m_cached() {}

  // Compiler generated copy ctor OK
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
  UnionNeuralInputTanhBondData(
      const UnionNeuralInputTanhBondData & /*_bond_rhs*/) = default;
#endif

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  UnionNeuralInputTanhBondData(UnionNeuralInputTanhBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF(
          (true && std::is_nothrow_move_constructible<bool>::value &&
           std::is_nothrow_move_constructible<bond::nullable<
               ::DynamicRank::NeuralInputTanhBondData> >::value &&
           std::is_nothrow_move_constructible<bond::nullable<
               ::DynamicRank::NeuralInputTanhUnaryBondData> >::value))
      : m_cached(std::move(_bond_rhs.m_cached)),
        m_neuralInputTanhBondData(
            std::move(_bond_rhs.m_neuralInputTanhBondData)),
        m_neuralInputTanhUnaryBondData(
            std::move(_bond_rhs.m_neuralInputTanhUnaryBondData)) {}
#endif

  template <typename Allocator>
  explicit UnionNeuralInputTanhBondData(Allocator *_bond_allocator)
      : m_cached(),
        m_neuralInputTanhBondData(*_bond_allocator),
        m_neuralInputTanhUnaryBondData(*_bond_allocator) {}

  // Compiler generated operator= OK
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
  UnionNeuralInputTanhBondData &operator=(
      const UnionNeuralInputTanhBondData &_bond_rhs) = default;
#endif

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  UnionNeuralInputTanhBondData &operator=(
      UnionNeuralInputTanhBondData &&_bond_rhs) {
    UnionNeuralInputTanhBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const UnionNeuralInputTanhBondData &_bond_other) const {
    return true && (m_cached == _bond_other.m_cached) &&
           (m_neuralInputTanhBondData ==
            _bond_other.m_neuralInputTanhBondData) &&
           (m_neuralInputTanhUnaryBondData ==
            _bond_other.m_neuralInputTanhUnaryBondData);
  }

  bool operator!=(const UnionNeuralInputTanhBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(UnionNeuralInputTanhBondData &_bond_other) {
    using std::swap;
    swap(m_cached, _bond_other.m_cached);
    swap(m_neuralInputTanhBondData, _bond_other.m_neuralInputTanhBondData);
    swap(m_neuralInputTanhUnaryBondData,
         _bond_other.m_neuralInputTanhUnaryBondData);
  }

  struct Schema;

 protected:
  void InitMetadata(const char * /*_bond_name*/,
                    const char * /*_bond_full_name*/) {}
};

inline void swap(UnionNeuralInputTanhBondData &_bond_left,
                 UnionNeuralInputTanhBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

// NeuralInputUseAsFloatBondData
struct NeuralInputUseAsFloatBondData
    : public ::DynamicRank::NeuralInputUnaryBondData {
  // 1: required_optional bond_meta::full_name name
  std::string name;

  NeuralInputUseAsFloatBondData() {
    InitMetadata("NeuralInputUseAsFloatBondData",
                 "DynamicRank.NeuralInputUseAsFloatBondData");
  }

  NeuralInputUseAsFloatBondData(const NeuralInputUseAsFloatBondData &_bond_rhs)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_rhs),
        name(_bond_rhs.name.get_allocator()) {
    InitMetadata("NeuralInputUseAsFloatBondData",
                 "DynamicRank.NeuralInputUseAsFloatBondData");
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputUseAsFloatBondData(NeuralInputUseAsFloatBondData &&_bond_rhs)
      BOND_NOEXCEPT_IF((true &&
                        std::is_nothrow_move_constructible<
                            ::DynamicRank::NeuralInputUnaryBondData>::value &&
                        std::is_nothrow_move_constructible<std::string>::value))
      : ::DynamicRank::NeuralInputUnaryBondData(std::move(_bond_rhs)),
        name(std::move(_bond_rhs.name)) {}
#endif

  template <typename Allocator>
  explicit NeuralInputUseAsFloatBondData(Allocator *_bond_allocator)
      : ::DynamicRank::NeuralInputUnaryBondData(_bond_allocator),
        name(*_bond_allocator) {
    InitMetadata("NeuralInputUseAsFloatBondData",
                 "DynamicRank.NeuralInputUseAsFloatBondData");
  }

  NeuralInputUseAsFloatBondData &operator=(
      const NeuralInputUseAsFloatBondData &_bond_rhs) {
    NeuralInputUseAsFloatBondData(_bond_rhs).swap(*this);
    return *this;
  }

#ifndef BOND_NO_CXX11_RVALUE_REFERENCES
  NeuralInputUseAsFloatBondData &operator=(
      NeuralInputUseAsFloatBondData &&_bond_rhs) {
    NeuralInputUseAsFloatBondData(std::move(_bond_rhs)).swap(*this);
    return *this;
  }
#endif

  bool operator==(const NeuralInputUseAsFloatBondData &_bond_other) const {
    return true &&
           (static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                *this) ==
            static_cast<const ::DynamicRank::NeuralInputUnaryBondData &>(
                _bond_other));
    // skip bond_meta::full_name field 'name'
  }

  bool operator!=(const NeuralInputUseAsFloatBondData &_bond_other) const {
    return !(*this == _bond_other);
  }

  void swap(NeuralInputUseAsFloatBondData &_bond_other) {
    using std::swap;
    ::DynamicRank::NeuralInputUnaryBondData::swap(_bond_other);
    // skip bond_meta::full_name field 'name'
  }

  struct Schema;

 protected:
  void InitMetadata(const char *_bond_name, const char *_bond_full_name) {
    ::DynamicRank::NeuralInputUnaryBondData::InitMetadata(_bond_name,
                                                          _bond_full_name);
    this->name = _bond_full_name;
  }
};

inline void swap(NeuralInputUseAsFloatBondData &_bond_left,
                 NeuralInputUseAsFloatBondData &_bond_right) {
  _bond_left.swap(_bond_right);
}

}  // namespace DynamicRank
