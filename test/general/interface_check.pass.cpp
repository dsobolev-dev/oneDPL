// -*- C++ -*-
//===-- interface_check.pass.cpp --------------------------------------------===//
//
// Copyright (C) Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// This file incorporates work covered by the following copyright and permission
// notice:
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
//
//===----------------------------------------------------------------------===//

#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/functional>
#include <oneapi/dpl/numeric>
#include <oneapi/dpl/iterator>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <CL/sycl.hpp>

template <typename Policy, typename NewName>
struct rebind_policy { using type = Policy; };

template <typename KernelName, typename NewName>
struct rebind_policy<oneapi::dpl::execution::device_policy<KernelName>, NewName>
{ using type = oneapi::dpl::execution::device_policy<NewName>; };

#if ONEDPL_FPGA_DEVICE
template <unsigned int factor, typename KernelName, typename NewName>
struct rebind_policy<oneapi::dpl::execution::fpga_policy<factor, KernelName>, NewName>
{  using type = oneapi::dpl::execution::fpga_policy<factor, NewName>; };
#endif


using oneapi::dpl::counting_iterator;
using oneapi::dpl::discard_iterator;
using oneapi::dpl::make_zip_iterator;

int main()
{
    cl::sycl::buffer<int, 1> buf{ cl::sycl::range<1>(10) };

    auto b = oneapi::dpl::begin(buf);
    auto e = oneapi::dpl::end(buf);
    auto z = make_zip_iterator(counting_iterator<int>(), discard_iterator());
    std::get<1>(z[0]) = oneapi::dpl::identity()(*counting_iterator<int>());
    return 0;
}