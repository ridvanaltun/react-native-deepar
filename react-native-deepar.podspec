require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name = "react-native-deepar"
  s.version = package["version"]
  s.summary = package["description"]
  s.homepage = package["homepage"]
  s.license = package["license"]
  s.authors = package["author"]

  s.platforms = { :ios => "11.0" }
  s.source = { :git => "https://github.com/ridvanaltun/react-native-deepar.git", :tag => "#{s.version}" }

  # s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386 arm64' }

  s.source_files = "ios/**/*.{h,m,mm}"
  s.vendored_frameworks = "ios/Frameworks/*.xcframework"

  s.dependency "React-Core"
end
