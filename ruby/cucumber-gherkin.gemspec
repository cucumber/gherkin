# frozen_string_literal: true

version = File.read(File.expand_path('VERSION', __dir__)).strip

Gem::Specification.new do |s|
  s.name        = 'cucumber-gherkin'
  s.version     = version
  s.authors     = ['Gáspár Nagy', 'Aslak Hellesøy', 'Steve Tooke']
  s.description = 'Gherkin parser'
  s.summary     = "#{s.name}-#{s.version}"
  s.email       = 'cukes@googlegroups.com'
  s.homepage    = 'https://github.com/cucumber/gherkin'
  s.platform    = Gem::Platform::RUBY
  s.license     = 'MIT'
  s.required_ruby_version = '>= 3.0'
  s.required_rubygems_version = '>= 3.2.8'

  s.metadata = {
    'bug_tracker_uri' => 'https://github.com/cucumber/gherkin/issues',
    'changelog_uri' => 'https://github.com/cucumber/gherkin/blob/main/CHANGELOG.md',
    'documentation_uri' => 'https://cucumber.io/docs/gherkin/',
    'mailing_list_uri' => 'https://groups.google.com/forum/#!forum/cukes',
    'source_code_uri' => 'https://github.com/cucumber/gherkin/blob/main/ruby'
  }

  s.add_runtime_dependency 'cucumber-messages', '> 25', '< 28'

  s.add_development_dependency 'rake', '~> 13.1'
  s.add_development_dependency 'rspec', '~> 3.13'
  s.add_development_dependency 'rubocop', '~> 1.26.0'

  s.executables      = %w[gherkin-ruby gherkin]
  s.files            = Dir['README.md', 'LICENSE', 'lib/**/*']
  s.rdoc_options     = ['--charset=UTF-8']
  s.require_path     = 'lib'
end
