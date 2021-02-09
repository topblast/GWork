import React from 'react';
import './section-box.styles.scss'


const SectionBox = (props) => {
  const {
    id,
    children
  } = props;
  return (
    <section id={`${id}`}>
      <div className='section-container'>{children}</div>
    </section>
  );
};

export default SectionBox;