class Location {
  const Location(this.line, this.column);

  static const int _unset = -1;

  static const empty = Location(_unset, _unset);

  final int line;

  final int column;

  bool get isEmpty => line == empty.line && column == empty.column;

  bool get hasColumn => column != _unset;
}
