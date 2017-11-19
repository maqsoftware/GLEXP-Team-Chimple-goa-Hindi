/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import React, { Component } from 'react';
import {
  Platform,
  StyleSheet,
  Text,
  View,
  Button
} from 'react-native'

import { StackNavigator } from 'react-navigation'

import LevelScreenLayout from './app/components/LevelScreenLayout'
import Lesson from './app/components/Lesson'

const HomeScreen = ({ navigation }) => (
  <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
    <Text>Home Screen</Text>
    <Button
      onPress={() => navigation.navigate('Lesson')}
      title="Go to Lessons"
    />
  </View>
)

const DetailsScreen = () => (
  <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
    <Text>Details Screen</Text>
  </View>
)

const RootNavigator = StackNavigator({
  Home: {
    screen: HomeScreen,
    navigationOptions: {
      headerTitle: 'Home',
    },
  },
  LessonList: {
    screen: LevelScreenLayout,
    navigationOptions: {
      headerTitle: 'Lessons',
    },
  },
  Lesson: {
    screen: Lesson,
    navigationOptions: {
      mode: 'modal',
      header: null  
    }
  }
})

export default RootNavigator