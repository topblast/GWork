import './App.scss';
import React from 'react';
import HeaderBar from './components/header-bar';
import IntroSection from './components/intro-section';
import WhySection from './components/why-section';
import HowSection from './components/how-section';
import CommunitySection from './components/community-section';
import ContactSection from './components/contact-section';
import FooterSection from './components/footer-section';

function App() {
  let links = [
    {
      caption: 'Why the Caribbean?'
    },
    {
      caption: 'How?'
    },
    {
      caption: 'Get Hired'
    },
    {
      caption: 'Our Services'
    },
    {
      caption: 'Clients'
    },
    {
      caption: 'Contact'
    }
  ];

  const doIntroCaption = () => (<p>WORLD-CLASS DEVELOPERS<br/>CARIBBEAN'S FINEST TALENT</p>)
  return (
    <div className="App">
      <HeaderBar links={links}></HeaderBar>
      <div className='header-filler'/>
      <IntroSection
        headingCaption={doIntroCaption()}
        buttonCaption={`JOIN THE TEAM`}
      />
      <WhySection/>
      <HowSection/>
      <CommunitySection/>
      <ContactSection/>
      <FooterSection/>
    </div>
  );
}

export default App;
