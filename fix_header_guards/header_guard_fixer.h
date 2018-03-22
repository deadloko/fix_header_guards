#ifndef HEADERGUARDFIXER_H
#define HEADERGUARDFIXER_H

#include <QString>

class HeaderGuardFixer {

public:
  static void FixHeaderGuardsInFile(const QString &file_name,
                                    bool is_edit_mode);

private:
  static QString CheckHeaderGuardsInText(const QString &file_text,
                                         const QString &file_name);

  static QString FixHeaderGuardsInText(const QString &file_text,
                                       const QString &file_name);
  static QString FindHeaderGuard(const QString &file_text);
  static QString MakeHeaderGuardFromFileName(const QString &file_name);
};

#endif // HEADERGUARDFIXER_H
