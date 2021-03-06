/***********************************************************************
	filename: 	CEGUIDragContainer.h
	created:	14/2/2005
	author:		Paul D Turner
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIDragContainer_h_
#define _CEGUIDragContainer_h_

#include "../CEGUIWindow.h"
#include "../CEGUIWindowFactory.h"
#include "CEGUIDragContainerProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
    /*!
    \brief
        Generic drag & drop enabled window class
    */
    class CEGUIEXPORT DragContainer : public Window
    {
    public:
        /*************************************************************************
            Constants
        *************************************************************************/
        static const String WidgetTypeName;     //!< Type name for DragContainer.
        static const String EventNamespace;     //!< Namespace for global events
        static const String EventDragStarted;   //!< Name of the event fired when the user begins dragging the thumb.
        static const String EventDragEnded;     //!< Name of the event fired when the user releases the thumb.
        static const String EventDragPositionChanged;   //!< Event fired when the drag position has changed.
        static const String EventDragEnabledChanged;    //!< Event fired when dragging is enabled or disabled.
        static const String EventDragAlphaChanged;      //!< Event fired when the alpha value used when dragging is changed.
        static const String EventDragMouseCursorChanged;//!< Event fired when the mouse cursor used when dragging is changed.
        static const String EventDragThresholdChanged;  //!< Event fired when the drag pixel threshold is changed.
        static const String EventDragDropTargetChanged; //!< Event fired when the drop target changes.

        /*************************************************************************
            Object Construction and Destruction
        *************************************************************************/
        /*!
        \brief
            Constructor for DragContainer objects
        */
        DragContainer(const String& type, const String& name);

        /*!
        \brief
            Destructor for DragContainer objects
        */
        virtual ~DragContainer(void);

        /*************************************************************************
        	Public Interface to DragContainer
        *************************************************************************/
        /*!
        \brief
            Return whether dragging is currently enabled for this DragContainer.

        \return
            - true if dragging is enabled and the DragContainer may be dragged.
            - false if dragging is disabled and the DragContainer may not be dragged.
        */
        bool isDraggingEnabled(void) const;

        /*!
        \brief
            Set whether dragging is currently enabled for this DragContainer.

        \param setting
            - true to enable dragging so that the DragContainer may be dragged.
            - false to disabled dragging so that the DragContainer may not be dragged.

        \return
            Nothing.
        */
        void setDraggingEnabled(bool setting);

        /*!
        \brief
            Return whether the DragContainer is currently being dragged.

        \return
            - true if the DragContainer is being dragged.
            - false if te DragContainer is not being dragged.
        */
        bool isBeingDragged(void) const;

        /*!
        \brief
            Return the current drag threshold in pixels.

            The drag threshold is the number of pixels that the mouse must be
            moved with the left button held down in order to commence a drag
            operation.
        
        \return
            float value indicating the current drag threshold value.
        */
        float getPixelDragThreshold(void) const;

        /*!
        \brief
            Set the current drag threshold in pixels.

            The drag threshold is the number of pixels that the mouse must be
            moved with the left button held down in order to commence a drag
            operation.

        \param pixels
            float value indicating the new drag threshold value.

        \return
            Nothing.
        */
        void setPixelDragThreshold(float pixels);

        /*!
        \brief
            Return the alpha value that will be set on the DragContainer while a drag operation is
            in progress.

        \return
            Current alpha value to use whilst dragging.
        */
        float getDragAlpha(void) const;

        /*!
        \brief
            Set the alpha value to be set on the DragContainer when a drag operation is
            in progress.

            This method can be used while a drag is in progress to update the alpha.  Note that
            the normal setAlpha method does not affect alpha while a drag is in progress, but
            once the drag operation has ended, any value set via setAlpha will be restored.

        \param alpha
            Alpha value to use whilst dragging.

        \return
            Nothing.
        */
        void setDragAlpha(float alpha);

        /*!
        \brief
            Return the Image currently set to be used for the mouse cursor when a
            drag operation is in progress.

        \return
            Image object currently set to be used as the mouse cursor when dragging.
        */
        const Image* getDragCursorImage(void) const;

        /*!
        \brief
            Set the Image to be used for the mouse cursor when a drag operation is
            in progress.

            This method may be used during a drag operation to update the current mouse
            cursor image.

        \param image
            Image object to be used as the mouse cursor while dragging.

        \return
            Nothing.
        */
        void setDragCursorImage(const Image* image);

        /*!
        \brief
            Set the Image to be used for the mouse cursor when a drag operation is
            in progress.

            This method may be used during a drag operation to update the current mouse
            cursor image.

        \param image
            One of the MouseCursorImage enumerated values.

        \return
            Nothing.
        */
        void setDragCursorImage(MouseCursorImage image);

        /*!
        \brief
            Set the Image to be used for the mouse cursor when a drag operation is
            in progress.

            This method may be used during a drag operation to update the current mouse
            cursor image.

        \param imageset
            String holding the name of the Imageset that contains the Image to be used.

        \param image
            Image defined for the Imageset \a imageset to be used as the mouse cursor
            when dragging.

        \return
            Nothing.

        \exception UnknownObjectException   thrown if either \a imageset or \a image are unknown.
        */
        void setDragCursorImage(const String& imageset, const String& image);

        /*!
        \brief
            Return the Window object that is the current drop target for the DragContainer.

            The drop target for a DragContainer is basically the Window that the DragContainer
            is within while being dragged.  The drop target may be 0 to indicate no target.

        \return
            Pointer to a Window object that contains the DragContainer whilst being dragged, or
            0 to indicate no current target.
        */
        Window* getCurrentDropTarget(void) const;

        /*!
        \brief
            Return whether sticky mode is enable or disabled.

        \return
            - true if sticky mode is enabled.
            - false if sticky mode is disabled.
        */
        bool isStickyModeEnabled() const;

        /*!
        \brief
            Enable or disable sticky mode.

        \param setting
            - true to enable sticky mode.
            - false to disable sticky mode.
        */
        void setStickyModeEnabled(bool setting);

        // Window class overrides.
        void getRenderingContext_impl(RenderingContext& ctx) const;

    protected:
        /*************************************************************************
        	Protected Implementation Methods
        *************************************************************************/
        /*!
        \brief
            Return whether the required minimum movement threshold before initiating dragging
            has been exceeded.

        \param local_mouse
            Mouse position as a pixel offset from the top-left corner of this window.

        \return
            - true if the threshold has been exceeded and dragging should be initiated.
            - false if the threshold has not been exceeded.
        */		
        bool isDraggingThresholdExceeded(const Point& local_mouse);

	    /*!
	    \brief
		    Initialise the required states to put the window into dragging mode.

        \return
            Nothing.
	    */
        void initialiseDragging(void);

        /*!
	    \brief
		    Update state for window dragging.

	    \param local_mouse
		    Mouse position as a pixel offset from the top-left corner of this window.

	    \return
		    Nothing.
	    */
        void doDragging(const Point& local_mouse);

        /*!
        \brief
            Method to update mouse cursor image
        */
        void updateActiveMouseCursor(void) const;


		/*!
		\brief
			Return whether this window was inherited from the given class name at some point in the inheritance hierarchy.

		\param class_name
			The class name that is to be checked.

		\return
			true if this window was inherited from \a class_name. false if not.
		*/
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name=="DragContainer")	return true;
			return Window::testClassName_impl(class_name);
		}


        /*************************************************************************
        	Overrides of methods in Window
        *************************************************************************/

        /*************************************************************************
        	Overrides for Event handler methods
        *************************************************************************/
        virtual void onMouseButtonDown(MouseEventArgs& e);
        virtual void onMouseButtonUp(MouseEventArgs& e);
        virtual void onMouseMove(MouseEventArgs& e);
        virtual void onCaptureLost(WindowEventArgs& e);
        virtual void onAlphaChanged(WindowEventArgs& e);
        virtual void onClippingChanged(WindowEventArgs& e);/*Window::drawSelf(z);*/
        virtual void onMoved(WindowEventArgs& e);

        /*************************************************************************
        	New Event handler methods
        *************************************************************************/
        /*!
        \brief
            Method called when dragging commences

        \param e
            WindowEventArgs object containing any relevant data.

        \return
            Nothing.
        */
        virtual void onDragStarted(WindowEventArgs& e);

        /*!
        \brief
            Method called when dragging ends.

        \param e
            WindowEventArgs object containing any relevant data.

        \return
            Nothing.
        */
        virtual void onDragEnded(WindowEventArgs& e);

        /*!
        \brief
            Method called when the dragged object position is changed.

        \param e
            WindowEventArgs object containing any relevant data.

        \return
            Nothing.
        */
        virtual void onDragPositionChanged(WindowEventArgs& e);

        /*!
        \brief
            Method called when the dragging state is enabled or disabled
        \param e
            WindowEventArgs object.
        \return
            Nothing.
        */
        virtual void onDragEnabledChanged(WindowEventArgs& e);

        /*!
        \brief
            Method called when the alpha value to use when dragging is changed.
        \param e
            WindowEventArgs object.
        \return
            Nothing.
        */
        virtual void onDragAlphaChanged(WindowEventArgs& e);

        /*!
        \brief
            Method called when the mouse cursor to use when dragging is changed.
        \param e
            WindowEventArgs object.
        \return
            Nothing.
        */
        virtual void onDragMouseCursorChanged(WindowEventArgs& e);

        /*!
        \brief
            Method called when the movement threshold required to trigger dragging is changed.
        \param e
            WindowEventArgs object.
        \return
            Nothing.
        */
        virtual void onDragThresholdChanged(WindowEventArgs& e);

        /*!
        \brief
            Method called when the current drop target of this DragContainer changes.
        \note
            This event fires just prior to the target field being changed.  The default implementation
            changes the drop target, you can examine the old and new targets before calling the default
            implementation to make the actual change (and fire appropriate events for the Window objects
            involved).
        \param e
            DragDropEventArgs object initialised as follows:
            - dragDropItem is initialised to the DragContainer triggering the event (typically 'this').
            - window is initialised to point to the Window which will be the new drop target.
        \return
            Nothing.
        */
        virtual void onDragDropTargetChanged(DragDropEventArgs& e);

        /*************************************************************************
        	Data
        *************************************************************************/
        bool    d_draggingEnabled;  //!< True when dragging is enabled.
        bool    d_leftMouseDown;    //!< True when left mouse button is down.
        bool    d_dragging;         //!< true when being dragged.
        UVector2 d_dragPoint;       //!< point we are being dragged at.
        UVector2 d_startPosition;   //!< position prior to dragging.
        float   d_dragThreshold;    //!< Pixels mouse must move before dragging commences.
        float   d_dragAlpha;        //!< Alpha value to set when dragging.
        float   d_storedAlpha;      //!< Alpha value to re-set when dragging ends.
        bool    d_storedClipState;  //!< Parent clip state to re-set.
        Window* d_dropTarget;       //!< Target window for possible drop operation.
        const Image* d_dragCursorImage; //!< Image to use for mouse cursor when dragging.
        bool d_dropflag;            //!< True when we're being dropped
        //! true when we're in 'sticky' mode.
        bool d_stickyMode;
        //! true after been picked-up / dragged via sticky mode
        bool d_pickedUp;

    private:
        /*************************************************************************
            Static properties for the Spinner widget
        *************************************************************************/
        static DragContainerProperties::DragAlpha       d_dragAlphaProperty;
        static DragContainerProperties::DragCursorImage d_dragCursorImageProperty;
        static DragContainerProperties::DraggingEnabled d_dragEnabledProperty;
        static DragContainerProperties::DragThreshold   d_dragThresholdProperty;
        static DragContainerProperties::StickyMode      d_stickyModeProperty;

        /*************************************************************************
        	Implementation methods
        *************************************************************************/
        /*!
        \brief
            Adds properties specific to the DragContainer base class.
        
        \return
            Nothing.
        */
        void addDragContainerProperties(void);
    };

} // End of  CEGUI namespace section


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	// end of guard _CEGUIDragContainer_h_
