#include "texteditor.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TextEditor editor;
    editor.show();

    return app.exec();
}

