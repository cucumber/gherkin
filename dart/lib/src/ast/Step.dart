import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/ast.dart';

class Step implements IHasLocation, INullSafetyObject
{
  static const empty = _InvalidStep();

  final String id;

  final Location _location;

  final String keyword;

  final String _keywordType;

  String get keywordType => _keywordType;

  final String text;

  final StepArgument argument;
  final DataTable _dataTable;
  final DocString _docString;

  const Step(this._location, this.keyword, this._keywordType, this.text, this.argument,
      {this.id=Strings.empty
      , DataTable dataTable = DataTable.empty
      , DocString docString = DocString.empty} )
      : _dataTable = dataTable
      , _docString = docString;

  @override
  Location get location => _location;

  DataTable get dataTable {
    if( _dataTable.isNotEmpty ) {
      return _dataTable;
    }
    if( argument is DataTable ) {
      return argument as DataTable;
    }
    return DataTable.empty;
  }

  DocString get docString {
    if( _docString.isNotEmpty ) {
      return _docString;
    }
    if( argument is DocString ) {
      return argument as DocString;
    }
    return DocString.empty;
  }

  @override
  bool get isEmpty => false;

  @override
  bool get isNotEmpty => !isEmpty;

  @override
  String toString() {
    final hexIdentityHashCode = hashCode.toRadixString(16);
    final sb = StringBuffer();
    sb..write(runtimeType)
      ..write('@')
      ..write(hexIdentityHashCode)
      ..write('[')
      ..write('keyword')
      ..write('=')
      ..write(keyword.isEmpty ? '<null>' : keyword)
      ..write(',')
      ..write('keywordType')
      ..write('=')
      ..write(keywordType.isEmpty ? '<null>' : keywordType)
      ..write(',')
      ..write('dataTable')
      ..write('=')
      ..write(dataTable.isEmpty ? '<null>' : dataTable)
      ..write(',')
      ..write('docString')
      ..write('=')
      ..write(docString.isEmpty ? '<null>' : docString)
      ..write(',')
      ..write('text')
      ..write('=')
      ..write(text.isEmpty ? '<null>' : text)
      ..write(']');
    return sb.toString();
  }

  @override
  bool operator ==(other) {
    return (other is Step)
        && other._location == _location
        && other.keyword == keyword
        && other.keywordType == keywordType
        && other.text == text
        && other.dataTable == dataTable
        && other.docString == docString
        && other.id == id
    ;
  }

  @override
  int get hashCode =>
      _location.hashCode
      ^ keyword.hashCode
      ^ keywordType.hashCode
      ^ text.hashCode
      ^ dataTable.hashCode
      ^ docString.hashCode
      ^ id.hashCode
  ;
}


/// Convenience implementation of an invalid [Step] instance.
class _InvalidStep extends Step
{
  const _InvalidStep()
    : super(Location.empty, Strings.empty, Strings.empty, Strings.empty, StepArgument.empty );

  @override
  bool get isEmpty => true;
}
