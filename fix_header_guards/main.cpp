#include <QCoreApplication>

#include <QStringList>

#include <QDebug>

#include <header_guard_fixer.h>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  QStringList arguments = app.arguments();
  arguments.pop_front();

  if (argc < 2) {
    return 2;
  }
  bool is_edit_mode = false;
  QString file_path = arguments.last();
  arguments.pop_back();

  for (auto argument : arguments) {
    if (argument == "-i") {
      is_edit_mode = true;
    }
  }

  HeaderGuardFixer::FixHeaderGuardsInFile(file_path, is_edit_mode);

  return app.exec();
}
