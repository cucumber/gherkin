import 'package:gherkin/core.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/pickles.dart';
import 'package:gherkin/language.dart';

class Pickle implements INullSafetyObject
{
  static const empty = _InvalidPickle();

  final String id;

  final String uri;

  final Location location;

  final String name;

  final String language;

  final List<PickleStep> steps;

  final List<PickleTag> tags;

  final List<String> astNodeIds;

  const Pickle(this.id, this.uri, this.location, this.name, this.language
    ,this.steps, this.tags, this.astNodeIds);

  @override
  bool get isEmpty => false;

  @override
  bool get isNotEmpty => !isEmpty;

  @override
  String toString() {
    final hexIdentityHashCode = hashCode.toRadixString(16);
    var sb = StringBuffer();
    sb
      ..write(runtimeType)
      ..write('@')
      ..write(hexIdentityHashCode)
      ..write('[')
      ..write('id')
      ..write('=')
      ..write(id.isEmpty ? '<null>' : id)
      ..write(',')
      ..write('uri')
      ..write('=')
      ..write(uri.isEmpty ? '<null>' : uri)
      ..write(',')
      ..write('location')
      ..write('=')
      ..write(location.isEmpty ? '<null>' : location)
      ..write(',')
      ..write('name')
      ..write('=')
      ..write(name.isEmpty ? '<null>' : name)
      ..write(',')
      ..write('language')
      ..write('=')
      ..write(language.isEmpty ? '<null>' : language)
      ..write(',')
      ..write('steps')
      ..write('=')
      ..write(steps.isEmpty ? '<null>' : steps)
      ..write(',')
      ..write('tags')
      ..write('=')
      ..write(tags.isEmpty ? '<null>' : tags)
      ..write(',')
      ..write('astNodeIds')
      ..write('=')
      ..write(astNodeIds.isEmpty ? '<null>' : astNodeIds)
      ..write(']');
    return sb.toString();
  }

  //https://api.flutter.dev/flutter/package-collection_collection/ListEquality-class.html
  @override
  bool operator ==(other) {
    return (other is Pickle)
        && other.id == id
        && other.uri == uri
        && other.location == location
        && other.name == name
        && other.language == language
        && other.steps == steps
        && other.tags == tags
        && other.astNodeIds == astNodeIds
    ;
  }

  @override
  int get hashCode =>
    id.hashCode
    ^ uri.hashCode
    ^ location.hashCode
    ^ name.hashCode
    ^ language.hashCode
    ^ steps.hashCode
    ^ tags.hashCode
    ^ astNodeIds.hashCode
    ;
}

/// Convenience implementation of an invalid [Pickle] instance.
class _InvalidPickle
    extends Pickle
{
  const _InvalidPickle()
      : super(Strings.empty, Strings.empty, Location.empty, Strings.empty, Strings.empty
    , const <PickleStep>[], const <PickleTag>[], const <String>[] );

  @override
  bool get isEmpty => true;
}
