// Test that the tri-valued complex range argument gets set appropriately.

// REQUIRES: clang-driver

// CHECK-FULL-RANGE: "-cc1"
// CHECK-FULL-RANGE: "-fcx-range=full"

// CHECK-LIMITED-RANGE: "-cc1"
// CHECK-LIMITED-RANGE: "-fcx-range=limited"

// CHECK-NONAN-RANGE: "-cc1"
// CHECK-NONAN-RANGE: "-fcx-range=nonan"

// RUN: %clang -### -c %s 2>&1 \
// RUN:   | FileCheck --check-prefix=CHECK-FULL-RANGE %s

// RUN: %clang -### -c -fcx-limited-range %s 2>&1 \
// RUN:   | FileCheck --check-prefix=CHECK-LIMITED-RANGE %s

// RUN: %clang -### -c -fcx-fortran-rules %s 2>&1 \
// RUN:   | FileCheck --check-prefix=CHECK-NONAN-RANGE %s
