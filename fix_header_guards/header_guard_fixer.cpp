#include "header_guard_fixer.h"

#include <QDebug>
#include <QFileInfo>
#include <QRegExp>

#include <QFile>

int HeaderGuardFixer::FixHeaderGuardsInFile(const QString &file_name,
                                            bool is_edit_mode) {
  QFile working_file(file_name);
  QFileInfo working_file_info(working_file);
  QString short_file_path = working_file_info.fileName();

  working_file.open(QIODevice::ReadOnly);
  QString file_contents = working_file.readAll();
  working_file.close();

  if (!is_edit_mode) {
    QString parsed_file = FixHeaderGuardsInText(file_contents, short_file_path);

    if (parsed_file != file_contents) {
      working_file.open(QIODevice::WriteOnly);
      QTextStream out(&working_file);
      out << parsed_file;

      working_file.close();
    }

    return 0;
  }

  bool is_guard_ok = CheckHeaderGuardsInText(file_contents, short_file_path);
  return is_guard_ok ? 0 : 1;
}

bool HeaderGuardFixer::CheckHeaderGuardsInText(const QString &file_text,
                                               const QString &file_name) {
  QString header_guard_from_file = MakeHeaderGuardFromFileName(file_name);

  QString first_guard = "#ifndef " + header_guard_from_file;
  QString second_guard = "#define " + header_guard_from_file;
  QString third_guard = "#endif // " + header_guard_from_file;

  if (!file_text.contains(first_guard) || !file_text.contains(second_guard) ||
      !file_text.contains(third_guard)) {
    return false;
  }

  return true;
}

QString HeaderGuardFixer::FixHeaderGuardsInText(const QString &file_text,
                                                const QString &file_name) {
  QString return_string = file_text;

  QString header_guard = FindHeaderGuard(file_text);
  QString header_guard_from_file = MakeHeaderGuardFromFileName(file_name);

  if (return_string.count(header_guard) > 3 ||
      !file_text.contains("#define " + header_guard)) {
    return "";
  }

  return_string.replace(header_guard, header_guard_from_file);

  QString endif_string = "#endif";
  int last_endif_position = return_string.lastIndexOf(endif_string);
  return_string.truncate(last_endif_position + endif_string.count());
  return_string.append("  // " + header_guard_from_file + "\n");

  return return_string;
}

QString HeaderGuardFixer::FindHeaderGuard(const QString &file_text) {
  QString header_guard_prefix = "#ifndef ";
  int header_guard_position = file_text.indexOf(header_guard_prefix);
  int header_guard_start_position =
      header_guard_position + header_guard_prefix.count();
  int space_position =
      file_text.indexOf(QRegExp(" |\n"), header_guard_start_position);

  return file_text.mid(header_guard_start_position,
                       space_position - header_guard_start_position);
}

QString
HeaderGuardFixer::MakeHeaderGuardFromFileName(const QString &file_name) {
  QString updated_file_name = file_name;
  updated_file_name.replace(".", "_");
  updated_file_name = updated_file_name.toUpper();

  return updated_file_name;
}
