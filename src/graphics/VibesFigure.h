/* ============================================================================
 *  tube-lib - VibesFigure class
 * ============================================================================
 *  Copyright : Simon Rohou
 *  License   : This program can be distributed under the terms of
 *              the MIT license. See the file LICENSE.
 *
 *  Author(s) : Simon Rohou
 *  Bug fixes : -
 *  Created   : 2015
 * ---------------------------------------------------------------------------- */

#ifndef VibesFigure_HEADER
#define VibesFigure_HEADER

#include "ibex.h"
#include "vibes.h"
#include <string>

class VibesFigure
{
  public:

    /**
     * \brief Create an object view: abstract class.
     *
     * \param figure_name a reference to the figure that will be displayed in the window's title
     */
    VibesFigure(const std::string& figure_name);

    /**
     * \brief Delete this figure.
     */
    ~VibesFigure() {};

    /**
     * \brief Return the name of the figure.
     *
     * \return figure's name
     */
    std::string name() const;

    /**
     * \brief Return x-position of the figure.
     *
     * \return x-position
     */
    double x() const;

    /**
     * \brief Return y-position of the figure.
     *
     * \return y-position
     */
    double y() const;

    /**
     * \brief Return figure's width.
     *
     * \return width
     */
    double width() const;

    /**
     * \brief Return figure's height.
     *
     * \return height
     */
    double height() const;

    /**
     * \brief Set figure's properties: position and dimensions.
     *
     * \param x x-position
     * \param y y-position
     * \param width width value
     * \param height height value
     */
    void setProperties(int x, int y, int width, int height);

    /**
     * \brief Save vibes-figure in SVG format.
     *
     * A file named {figure_name}{suffix}.svg is created in the current directory.
     *
     * \param suffix optional part name that can be added to figure_name, empty by default
     */
    void saveSVG(const std::string& suffix = "") const;

    /**
     * \brief Display the figure.
     *
     * This is a virtual method to overload.
     */
    virtual void show() const = 0;

  protected:
    std::string m_name;
    double m_x, m_y, m_width, m_height;
};

#endif