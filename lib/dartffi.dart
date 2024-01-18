import 'dart:ffi';
import 'package:ffi/ffi.dart';

typedef GetSmartDataFunc = Pointer<Utf8> Function(Int8 driveLetter);
typedef GetSmartData = Pointer<Utf8> Function(int driveLetter);

class SmartDataFFI {
  late DynamicLibrary _lib;
  late GetSmartData _getSmartData;

  SmartDataFFI() {
    // Replace 'path_to_your_cpp_library' with the actual path of your compiled library
    _lib = DynamicLibrary.open("C:\\Users\\joshu\\Desktop\\driveadviser\\rawreaderror.dll");
    _getSmartData = _lib
        .lookup<NativeFunction<GetSmartDataFunc>>('getRawReadErrorRateWrapper')
        .asFunction();
  }

  String getSmartData(String driveLetter) {
    if (driveLetter.length != 1) {
      throw ArgumentError("Drive letter must be a single character");
    }

    final result = _getSmartData(driveLetter.codeUnitAt(0));
    return result.toDartString();
  }
}
