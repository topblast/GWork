import { Link } from '@material-ui/core';
import React from 'react';

const LinkButton = props => {
  const {
    caption, 
    link,
    index
  } = props;

  const preventDefault = (event) => event.preventDefault();

  return (
    <div className='nav-link'>
      <Link 
        id={`nav-link-${index}`}
        href={link}
        onClick={preventDefault}>{caption}</Link>
    </div>
  );
}

export default LinkButton;