import React, { useState, useEffect } from 'react'
import axios from 'axios'
import ReactPaginate from 'react-paginate';

import './Students.css'

export default function Students() {
  const [offset, setOffset] = useState(0);
  const [students, setStudents] = useState([]);
  const [pageCount, setPageCount] = useState(1);

  const perPage = 5;
  const studentsPerPage = students.slice(offset, offset + perPage);

  useEffect(() => {
    axios.get(`http://localhost:8080/students`)
         .then(res => {
            const students = res.data.students;
            setStudents(students);
            setPageCount(Math.ceil(students.length / perPage));
        });
  }, []);

  function handlePageClick(event) {
      setOffset(event.selected * perPage);
  }

  return (
    <div>
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Grade</th>
          </tr>
        </thead>
        <tbody>
        {
          studentsPerPage.map(student => (
            <Student 
              key={student.id} 
              name={student.name} 
              grade={student.grade}
            />
          ))
        }
        </tbody>
      </table>
      <ReactPaginate
        previousLabel={"prev"}
        nextLabel={"next"}
        pageCount={pageCount}
        onPageChange={handlePageClick}
        containerClassName={"pagination"}
        subContainerClassName={"pages pagination"}
        activeClassName={"active"}/>
    </div>
  );
}

function Student({ name, grade }) {
  return (
    <tr>
      <td>{name}</td>
      <td>{grade}</td>
    </tr>
  );
}
