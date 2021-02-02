import React, { Component } from 'react';
import axios from 'axios';

import Students from './components/Students';

export default class App extends Component {
    constructor(props) {
        super(props);

        this.state = {
            className: '',
            teacherName: '',
            average: 0
        };
    }

    componentDidMount() {
        this.fetchClass();
        this.fetchTeacher();
        this.fetchAverage();
    }

    fetchClass() {
        axios
            .get(`http://localhost:8080/classroom`)
            .then(res => this.setState({ className: res.data.name }));
    }


    fetchTeacher() {
        axios
            .get(`http://localhost:8080/teacher`)
            .then(res => this.setState({ teacherName: res.data.name }));
    }

    fetchAverage() {
        axios
            .get(`http://localhost:8080/average`)
            .then(res => this.setState({ average: res.data.average }));
    }

    render() {
        const { className, teacherName, average } = this.state;

        return (
            <div>
                <h1>Class: { className }</h1>
                <h2>Teacher: { teacherName }</h2>
                <h2>Students</h2>
                <Students />
                <h2>Class Average: { average }</h2>
            </div>
        );
    }
}
