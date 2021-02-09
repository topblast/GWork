import { Link } from '@material-ui/core';
import React from 'react';
import './intro.styles.scss';

const IntroSection = (props) => {
  const {
    headingCaption,
    buttonCaption,
    buttonLink
  } = props;
  
  const preventDefault = (event) => event.preventDefault();

  return (
    <section id="intro">
      <h1>{headingCaption}</h1>
      <Link className='link-button' href={buttonLink} onClick={preventDefault}>{buttonCaption}</Link>
    </section>
  );
};

export default IntroSection;