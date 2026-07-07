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

  final DataTable _dataTable;
  final DocString _docString;

  const Step(this._location, this.keyword, this._keywordType, this.text,
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
    return DataTable.empty;
  }

  DocString get docString {
    if( _docString.isNotEmpty ) {
      return _docString;
    }
    return DocString.empty;
  }

  @override
  bool get isEmpty => false;

  @override
  bool get isNotEmpty => !isEmpty;
}


/// Convenience implementation of an invalid [Step] instance.
class _InvalidStep extends Step
{
  const _InvalidStep()
    : super(Location.empty, Strings.empty, Strings.empty, Strings.empty);

  @override
  bool get isEmpty => true;
}
