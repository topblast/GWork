import { AppBar } from '@material-ui/core';
import React from 'react';
import logoSVG from './logo1.svg';
import './header.styles.scss';
import LinkButton from './LinkButton';

const HeaderBar = props => {
  const {links} = props;

  return (
    <section className='header-section'>
      <AppBar className='header-container' color="inherit">
        <div className='logo-container'>
          <img alt="DigiCaribbean Logo" src={logoSVG} />
        </div>
        <div className='link-container'>
          {links.map((link, index) => {
            return (<LinkButton caption={link.caption} index={index}/>);
          })}
        </div>
      </AppBar>
    </section>)
}

export default HeaderBar;