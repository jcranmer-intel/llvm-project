// RUN: %clang_cc1 %s -O0 -emit-llvm -triple x86_64-unknown-unknown -fuse-complex-intrinsics -fcx-range=limited -o - | FileCheck %s --check-prefixes=CHECK-COMMON,CHECK-LIMITED
// RUN: %clang_cc1 %s -O0 -emit-llvm -triple x86_64-unknown-unknown -fuse-complex-intrinsics -fcx-range=nonan -o - | FileCheck %s --check-prefixes=CHECK-COMMON,CHECK-NO-NAN
// RUN: %clang_cc1 %s -O0 -emit-llvm -triple x86_64-unknown-unknown -fuse-complex-intrinsics -fcx-range=full -o - | FileCheck %s --check-prefixes=CHECK-COMMON,CHECK-FULL

_Complex float range_limited(_Complex float a, _Complex float b) {
// CHECK-COMMON: @range_limited
// CHECK-COMMON: call{{.*}}complex.fmul{{.*}} #[[LIMITED:[0-9]+]]
// CHECK-COMMON: call{{.*}}complex.fdiv{{.*}} #[[LIMITED]]
#pragma STDC CX_LIMITED_RANGE ON
  return a * b + a / b;
}

_Complex float range_full(_Complex float a, _Complex float b) {
// CHECK-COMMON: @range_full
// CHECK-COMMON: call{{.*}}complex.fmul{{.*}} #[[FULL:[0-9]+]]
// CHECK-COMMON: call{{.*}}complex.fdiv{{.*}} #[[FULL]]
#pragma STDC CX_LIMITED_RANGE OFF
  return a * b + a / b;
}

_Complex float range_default(_Complex float a, _Complex float b) {
// CHECK-LIMITED: @range_default
// CHECK-LIMITED: call{{.*}}complex.fmul{{.*}} #[[LIMITED]]
// CHECK-LIMITED: call{{.*}}complex.fdiv{{.*}} #[[LIMITED]]
// CHECK-NO-NAN: @range_default
// CHECK-NO-NAN: call{{.*}}complex.fmul{{.*}} #[[LIMITED]]
// CHECK-NO-NAN: call{{.*}}complex.fdiv{{.*}} #[[NONAN:[0-9]+]]
// CHECK-FULL: @range_default
// CHECK-FULL: call{{.*}}complex.fmul{{.*}} #[[FULL]]
// CHECK-FULL: call{{.*}}complex.fdiv{{.*}} #[[FULL]]
  return a * b + a / b;
}

_Complex float range_scoped(_Complex float a, _Complex float b) {
// CHECK-COMMON: @range_scoped
// CHECK-COMMON: call{{.*}}complex.fmul{{.*}} #[[FULL]]
// CHECK-COMMON: call{{.*}}complex.fdiv{{.*}} #[[FULL]]
#pragma STDC CX_LIMITED_RANGE OFF
  _Complex float res = a * b;
  {
#pragma STDC CX_LIMITED_RANGE DEFAULT
    res += a / b;
  }
  return res;
}

// CHECK-COMMON: attributes #[[LIMITED]] = { "complex-range"="limited" }
// CHECK-COMMON: attributes #[[FULL]] = { "complex-range"="full" }
// CHECK-NO-NAN: attributes #[[NONAN]] = { "complex-range"="no-nan" }
