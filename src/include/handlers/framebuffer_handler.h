#ifndef FRAMEBUFFER_HANDLER_H
#define FRAMEBUFFER_HANDLER_H

void FramebufferSetup();
void CleanFramebuffer(uint8_t *framebuffer);
uint8_t* GetMainFramebuffer();
uint8_t* GetStatubarFramebuffer();
uint8_t* GetNotificationFramebuffer();
uint8_t* GetPopupFramebuffer();

#endif // FRAMEBUFFER_HANDLER_H