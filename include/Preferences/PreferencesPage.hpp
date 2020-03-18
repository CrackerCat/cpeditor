/*
 * Copyright (C) 2019-2020 Ashar Khan <ashar786khan@gmail.com>
 *
 * This file is part of CP Editor.
 *
 * CP Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * I will not be responsible if CP Editor behaves in unexpected way and
 * causes your ratings to go down and or lose any important contest.
 *
 * Believe Software is "Software" and it isn't immune to bugs.
 *
 */

/*
 * This is an abstract base class for a page in the preferences.
 *
 * It provides the basic buttons: Default, Reset, and Apply.
 *
 * Default: Set the setting in the current page to default.
 * Reset: Clear unsaved settings.
 * Apply: Save settings without exiting.
 *
 * When the user is about to leave the current page, if there are unsaved changes, the user will
 * be asked whether to save the changes, discard the changes, or stay in the current page.
 */

#ifndef PREFERENCESPAGE_HPP
#define PREFERENCESPAGE_HPP

#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

class PreferencesPage : public QWidget
{
    Q_OBJECT

  private:
    /*
     * @brief query for whether the settings are different from the UI
     */
    virtual bool areSettingsChanged() = 0;

    /*
     * @brief update the UI, make it the same as the default values
     * @note you don't need to call updateButtons() in this function
     */
    virtual void makeUITheSameAsDefault() = 0;

    /*
     * @brief update the UI, make it the same as the settings
     * @note you don't need to call updateButtons() in this function
     */
    virtual void makeUITheSameAsSettings() = 0;

    /*
     * @brief update the settings, make it the same as the UI
     * @note you don't need to call updateButtons() in this function
     */
    virtual void makeSettingsTheSameAsUI() = 0;

  public:
    /*
     * @brief construct a PreferencesPage
     */
    explicit PreferencesPage(QWidget *parent = nullptr);

    /*
     * @brief a virtual destructor that does nothing
     * @note the widgets are destructed by Qt, so we shouldn't destruct them in the codes
     */
    virtual ~PreferencesPage(){};

    /*
     * @brief ask the user whether to save, discard or cancel if there are unsaved changes
     * @return return true if there is no unsaved change or the changes are saved/discarded
     */
    bool aboutToExit();

  public slots:
    /*
     * @brief update the UI, make it the same as the settings, and update buttons
     */
    void loadSettings();

  signals:
    /*
     * @brief the settings are applied
     */
    void settingsApplied();

  protected:
    /*
     * @brief add a layout in the UI
     */
    void addLayout(QLayout *layout);

    /*
     * @brief add a widget in the UI
     */
    void addWidget(QWidget *widget);

    /*
     * @brief add an item in the UI
     */
    void addItem(QLayoutItem *item);

  protected slots:
    /*
     * @brief enable/disable the reset button and the apply button
     * @note this should be invoked when the UI/the settings are changed
     */
    void updateButtons();

  private slots:
    /*
     * @brief update the UI, make it the same as the default values, and update buttons
     */
    void loadDefault();

    /*
     * @brief update the settings, make it the same as the UI, and update buttons
     */
    void applySettings();

  private:
    /*
     * The UI structure:
     *
     * mainLayout:
     *  - scrollArea
     *    - scrollAreaWidget
     *      - settingsLayout
     *        - setting 1 in the derived class
     *        - ...
     *  - buttonsLayout
     *    - defaultButton
     *    - resetButton
     *    - buttonsSpacer
     *    - applyButton
     */

    QVBoxLayout *mainLayout = nullptr;     // The main layout of the page
    QScrollArea *scrollArea = nullptr;     // The scroll area to place the settings
    QWidget *scrollAreaWidget = nullptr;   // The widget in the scroll area with settingsLayout as its layout
    QVBoxLayout *settingsLayout = nullptr; // The layout for the settings
    QHBoxLayout *buttonsLayout = nullptr;  // The layout for the Default, Reset, and Apply buttons
    QSpacerItem *buttonsSpacer = nullptr;  // The spacer to put Default and Reset the to left and put Apply to the right
    QPushButton *defaultButton = nullptr;  // The button to set the UI to the default values
    QPushButton *resetButton = nullptr;    // The button to set the UI to the saved settings
    QPushButton *applyButton = nullptr;    // The button to save the UI to the settings
};

#endif // PREFERENCESPAGE_HPP
