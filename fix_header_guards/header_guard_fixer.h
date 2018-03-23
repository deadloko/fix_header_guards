#ifndef HEADER_GUARD_FIXER_H
#define HEADER_GUARD_FIXER_H

#include <QString>

class HeaderGuardFixer {

public:
  static int FixHeaderGuardsInFile(const QString &file_name, bool is_edit_mode);

private:
  static bool CheckHeaderGuardsInText(const QString &file_text,
                                      const QString &file_name);

  static QString FixHeaderGuardsInText(const QString &file_text,
                                       const QString &file_name);
  static QString FindHeaderGuard(const QString &file_text);
  static QString MakeHeaderGuardFromFileName(const QString &file_name);
};

#endif  // HEADER_GUARD_FIXER_H
