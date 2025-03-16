#include <stdio.h>

#define UI_LINUX
#define UI_IMPLEMENTATION
#include "libs/luigi.h"

UIWindow *window;

// TODO see luigi_example.linux.c for #ifdef UI_LINUX
void ui_init() {
  UIInitialise();
  window = UIWindowCreate(0, 0, "Test Window", 0, 0);
}

int selected;

int MyTableMessage(UIElement *element, UIMessage message, int di, void *dp) {
  if (message == UI_MSG_TABLE_GET_ITEM) {
    UITableGetItem *m = (UITableGetItem *)dp;
    m->isSelected = selected == m->index;

    if (m->column == 0) {
      return snprintf(m->buffer, m->bufferBytes, "Item %d", m->index);
    } else {
      return snprintf(m->buffer, m->bufferBytes, "other column %d", m->index);
    }
  } else if (message == UI_MSG_LEFT_DOWN) {
    int hit = UITableHitTest((UITable *)element, element->window->cursorX,
                             element->window->cursorY);

    if (selected != hit) {
      selected = hit;

      if (!UITableEnsureVisible((UITable *)element, selected)) {
        UIElementRepaint(element, NULL);
      }
    }
  }

  return 0;
}

// inline static applicable only to the same translation unit ( i.e. source
// file)
int ui_render_loop() {
  {
    UITable *table =
        UITableCreate(&window->e, 0, "Column 1\tColumn 2\tColumn 3");
    table->itemCount = 6;                  // item per column?
    table->e.messageUser = MyTableMessage; // table_onUserMessage;
    UITableResizeColumns(table);
  }
  return UIMessageLoop();
}