import 'dart:convert';
import 'dart:io';

import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';
import 'package:path/path.dart';

/// The bundled dialect data, relative to this package's root.
const _dialectsAssetRelativePath = 'lib/src/assets/gherkin-languages.json';

/// Loads the bundled `gherkin-languages.json` resource into a map of dialects
/// keyed by language tag.
///
/// The asset ships inside this package under [_dialectsAssetRelativePath]. It
/// is located by resolving this package's root via `.dart_tool/
/// package_config.json` (walking up from the current directory), so loading
/// does not depend on the current working directory and works when the package
/// is consumed as a dependency. Falls back to a working-directory-relative
/// lookup when no package config is available.
///
/// Throws an [Exception] if the resource cannot be found.
Map<String, GherkinLanguageKeywords> loadGherkinLanguagesFromJsonAsset() {
  final file = _resolveDialectsAsset();
  if (file == null || !file.existsSync()) {
    throw Exception(
      'Gherkin language resource not found: $_dialectsAssetRelativePath',
    );
  }
  return _parseLanguages(file.readAsStringSync());
}

File? _resolveDialectsAsset() {
  // Preferred: resolve relative to this package's root, located through the
  // package config. Independent of the current working directory.
  final packageRoot = _findPackageRoot('cucumber_gherkin');
  if (packageRoot != null) {
    final file = File.fromUri(packageRoot.resolve(_dialectsAssetRelativePath));
    if (file.existsSync()) {
      return file;
    }
  }
  // Fallback: look for the asset relative to the current directory (e.g. when
  // run from the package root without a package config).
  final fallback = File(
    join(Directory.current.path, _dialectsAssetRelativePath),
  );
  return fallback.existsSync() ? fallback : null;
}

/// Returns the root directory URI of [packageName] by reading the nearest
/// `.dart_tool/package_config.json`, or `null` if it cannot be determined.
Uri? _findPackageRoot(String packageName) {
  final configFile =
      _findPackageConfig(Directory.current) ?? _findPackageConfigFromScript();
  if (configFile == null) {
    return null;
  }
  try {
    final config =
        json.decode(configFile.readAsStringSync()) as Map<String, dynamic>;
    final packages =
        (config['packages'] as List<dynamic>).cast<Map<String, dynamic>>();
    for (final package in packages) {
      if (package['name'] == packageName) {
        final rootUri = package['rootUri'] as String;
        // `rootUri` is relative to the package_config.json's directory.
        final base = configFile.parent.uri;
        return base.resolve(rootUri.endsWith('/') ? rootUri : '$rootUri/');
      }
    }
  } on FormatException {
    return null;
  }
  return null;
}

/// Walks up from the running script's directory looking for
/// `.dart_tool/package_config.json`. Handles the case where the current
/// working directory is unrelated to the package (e.g. the package is used as
/// a dependency, or the entrypoint is run from another directory).
File? _findPackageConfigFromScript() {
  final script = Platform.script;
  if (script.scheme != 'file') {
    return null;
  }
  return _findPackageConfig(File.fromUri(script).parent);
}

/// Walks up from [start] looking for `.dart_tool/package_config.json`.
File? _findPackageConfig(Directory start) {
  var dir = start.absolute;
  while (true) {
    final candidate = File(join(dir.path, '.dart_tool', 'package_config.json'));
    if (candidate.existsSync()) {
      return candidate;
    }
    final parent = dir.parent;
    if (parent.path == dir.path) {
      return null;
    }
    dir = parent;
  }
}

Map<String, GherkinLanguageKeywords> _parseLanguages(String languagesString) {
  final map = json.decode(languagesString) as Map<String, dynamic>;
  final languages = <String, GherkinLanguageKeywords>{};
  for (final entry in map.entries) {
    languages[entry.key] = GherkinLanguageKeywords.fromJson(
      entry.value as Map<String, dynamic>,
    );
  }
  return languages;
}
