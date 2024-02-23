#include <slint-interpreter.h>

int main(int argc, char **argv) {
  slint::interpreter::ComponentCompiler compiler;
  auto definition = compiler.build_from_path(SOURCE_DIR "/ui/appwindow.slint");

  for (auto diagnostic : compiler.diagnostics()) {
    std::cerr << (diagnostic.level ==
                          slint::interpreter::DiagnosticLevel::Warning
                      ? "warning: "
                      : "error: ")
              << diagnostic.message << std::endl;
    std::cerr << "location: " << diagnostic.source_file;
    if (diagnostic.line > 0)
      std::cerr << ":" << diagnostic.line;
    if (diagnostic.column > 0)
      std::cerr << ":" << diagnostic.column;
    std::cerr << std::endl;
  }

  if (!definition) {
    std::cerr << "compilation failure!" << std::endl;
    return EXIT_FAILURE;
  }

  auto ui = definition->create();

  ui->set_callback("request-increase-value", [&](auto) {
    ui->set_property("counter",
                     ui->get_property("counter")->to_number().value() + 1);
    return slint::interpreter::Value();
  });

  ui->run();
  return 0;
}
