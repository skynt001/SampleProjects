﻿using System;
using System.Windows;
using System.Windows.Controls;

namespace GridControl.Extended
{
    public class RowDefinitionExtended : RowDefinition
    {

        public static DependencyProperty VisibleProperty;

        public Boolean Visible {
            get { return (Boolean)GetValue(VisibleProperty); }
            set { SetValue(VisibleProperty, value); }
        }

        static RowDefinitionExtended()
        {
            VisibleProperty = DependencyProperty.Register("Visible", typeof(Boolean), 
                typeof(RowDefinitionExtended), new PropertyMetadata(true, new PropertyChangedCallback(OnVisibleChanged)));

            RowDefinition.HeightProperty.OverrideMetadata(typeof(RowDefinitionExtended), 
                new FrameworkPropertyMetadata(new GridLength(1, GridUnitType.Star), null, 
                new CoerceValueCallback(CoerceHeight)));

            RowDefinition.MinHeightProperty.OverrideMetadata(typeof(RowDefinitionExtended), 
                new FrameworkPropertyMetadata((Double)0, null, new CoerceValueCallback(CoerceMinHeight)));
        }

        public static void SetVisible(DependencyObject obj, Boolean nVisible)
        {
            obj.SetValue(VisibleProperty, nVisible);
        }

        public static Boolean GetVisible(DependencyObject obj)
        {
            return (Boolean)obj.GetValue(VisibleProperty);
        }

        static void OnVisibleChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            obj.CoerceValue(RowDefinition.HeightProperty);
            obj.CoerceValue(RowDefinition.MinHeightProperty);
        }

        static Object CoerceHeight(DependencyObject obj, Object nValue)
        {
            return (((RowDefinitionExtended)obj).Visible) ? nValue : new GridLength(0);
        }

        static Object CoerceMinHeight(DependencyObject obj, Object nValue)
        {
            return (((RowDefinitionExtended)obj).Visible) ? nValue : (Double)0;
        }

    }
}
