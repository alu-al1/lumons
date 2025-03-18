#include <stdio.h>

#define UI_LINUX
#define UI_IMPLEMENTATION
#include "../lib/luigi.h" //TODO fix this

UIWindow *window;

#ifndef UI_SPLIT_PANE_HORIZONTAL
#define UI_SPLIT_PANE_HORIZONTAL (0 << 0)
#endif

// TODO see luigi_example.linux.c for #ifdef UI_LINUX
void ui_init() {
  UIInitialise();
  window = UIWindowCreate(0, 0, "Test Window", 0, 0);
}

int selected;

int MyTableMessage(UIElement *element, UIMessage message, int di, void *dp) {
  UITable *t = (UITable *)element;

  if (message == UI_MSG_TABLE_GET_ITEM) {
    UITableGetItem *m = (UITableGetItem *)dp;
    m->isSelected = selected == m->index;

    if (m->column == 0) {
      return snprintf(m->buffer, m->bufferBytes, "Item %d", m->index);
    } else {
      return snprintf(m->buffer, m->bufferBytes, "Other Column %d", m->index);
    }
  }

  if (message == UI_MSG_LEFT_DOWN) {
    int hit =
        UITableHitTest(t, element->window->cursorX, element->window->cursorY);

    if (selected != hit) {
      selected = hit;
      if (!UITableEnsureVisible(t, selected)) {
        UIElementRepaint(&t->e, NULL);
      }
    }
  }

  if (message == UI_MSG_VALUE_CHANGED) {
    printf("UI_MSG_VALUE_CHANGED received!\n");

    t->itemCount = 8;
    UITableResizeColumns(t);
    UIElementRefresh(&t->e);
  }

  return 0;
}

// inline static applicable only to the same translation unit ( i.e. source
// file)
int ui_render_loop() {

  UISplitPane *split_8_4 =
      UISplitPaneCreate(&window->e, UI_SPLIT_PANE_HORIZONTAL,
                        0.8f); // Adjust split ratio
  UITabPane *col_8, *col_4;

  col_8 = UITabPaneCreate(&split_8_4->e,
                          UI_PANEL_GRAY | UI_ELEMENT_H_FILL | UI_ELEMENT_V_FILL,
                          NULL);
  col_4 = UITabPaneCreate(&split_8_4->e,
                          UI_PANEL_GRAY | UI_ELEMENT_H_FILL | UI_ELEMENT_V_FILL,
                          NULL);

  {
    UITable *table = UITableCreate(&col_8->e, 0,
                                   "Monitor\tUID\tController type\tBrightness");
    table->e.messageUser = MyTableMessage; // table_onUserMessage;

    // simulate new data - will trigger repaint
    UIElementMessage(&(table->e), UI_MSG_VALUE_CHANGED, 0, 0);
  }

  {
    UITable *table = UITableCreate(&col_4->e, 0,
                                   "Monitor\tUID\tController type\tBrightness");
    table->e.messageUser = MyTableMessage; // table_onUserMessage;

    // simulate new data - will trigger repaint
    UIElementMessage(&(table->e), UI_MSG_VALUE_CHANGED, 0, 0);
  }
  return UIMessageLoop();
}