<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Frei-/Gebucht-Informationen verwenden | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-extended.php" title="22. Kapitel - Erweiterte Funktionen"><link rel="prev" href="groupware-client-extended-ol-syncfreq.php" title="22.6. Synchronisationsfrequenz von E-Mails konfigurieren"><link rel="next" href="groupware-client-extended-multiplesenders.php" title="22.8. Mehrere Absenderadressen">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="groupware-client-extended-freebusy.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-extended-freebusy.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">22.7. Frei-/Gebucht-Informationen verwenden</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-extended-ol-syncfreq.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">22. Kapitel - Erweiterte Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-multiplesenders.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-extended-freebusy"></a>22.7. Frei-/Gebucht-Informationen verwenden</h2></div></div></div><a class="indexterm" name="groupware-client-extended-freebusy1"></a><a class="indexterm" name="groupware-client-extended-freebusy2"></a><p>Sollten Ihnen Kollegen ihren Kalender nicht zum Lesen freigegeben haben, k&ouml;nnen Sie
            dennoch f&uuml;r die Organisation eines gemeinsamen Termins herausfinden, wann die Kollegen
            keine anderen Termine in ihren Kalendern eingetragen haben. Diese Information wird &uuml;ber
            das Frei-/Gebucht-System bereitgestellt.</p><p>Bevor Sie die Frei-/Gebucht-Daten nutzen k&ouml;nnen, m&uuml;ssen Sie zuerst die korrekte
            Adresse zum Abruf der Daten in Outlook hinterlegen. Gehen Sie dazu wie folgt vor:</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-extended-freebusy-ol2010"></a>22.7.1. Outlook 2013 und 2010</h3></div></div></div><div class="procedure"><ol type="1"><li><p>W&auml;hlen Sie in Outlook im Men&uuml; <span class="guimenu">Datei</span> den Punkt
                            <span class="guisubmenu">Optionen</span> aus.</p></li><li><p>Klicken Sie auf die Schaltfl&auml;che <span class="guibutton">Kalender</span>.</p></li><li><p>W&auml;hlen Sie nun die Schaltfl&auml;che
                            <span class="guibutton">Frei/Gebucht-Optionen</span> aus.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/freebusy-ol2010-option01.png"></div></div></li><li><p>Tragen Sie den Suchpfad bei <span class="guilabel">Suchen unter</span> ein.</p><p>Die Adresse lautet
                            <strong class="userinput"><code>https://intranator.net.lan/freebusy/%NAME%@%SERVER%.ifb</code></strong>.</p><p>Verwenden Sie den Namen Ihres Intranator Servers und geben die Adresse
                        ansonsten genau so wie hier gezeigt ein.</p><p>Da der Intranator Server die Frei/Gebucht-Informationen automatisch
                        erzeugt, darf das Kontrollk&auml;stchen <span class="guilabel">Ver&ouml;ffentlichen
                            unter</span> nicht gesetzt sein.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/freebusy-ol2010-option02.png"></div></div></li></ol></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-extended-freebusy-ol2007"></a>22.7.2. Outlook 2007 und Outlook 2003</h3></div></div></div><div class="procedure"><ol type="1"><li><p>W&auml;hlen Sie in Outlook im Men&uuml; <span class="guimenu">Extras</span> den Punkt
                            <span class="guisubmenu">Optionen</span> aus.</p></li><li><p>Klicken Sie auf die Schaltfl&auml;che
                        <span class="guibutton">Kalenderoptionen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/freebusy-ol2007-option01.png"></div></div></li><li><p>W&auml;hlen Sie nun die Schaltfl&auml;che
                            <span class="guibutton">Frei/Gebucht-Optionen</span> aus.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/freebusy-ol2007-option02.png"></div></div></li><li><p>Tragen Sie den Suchpfad bei <span class="guilabel">Suchen unter</span> ein.</p><p>Die Adresse lautet
                            <strong class="userinput"><code>https://intranator.net.lan/freebusy/%NAME%@%SERVER%.ifb</code></strong>.</p><p>Verwenden Sie den Namen Ihres Intranator Servers und geben die Adresse
                        ansonsten genau so wie hier gezeigt ein.</p><p>Da der Intranator Server die Frei/Gebucht-Informationen automatisch
                        erzeugt, darf das Kontrollk&auml;stchen <span class="guilabel">Ver&ouml;ffentlichen
                            unter</span> nicht gesetzt sein.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/freebusy-ol2007-option03.png"></div></div></li></ol></div><a class="indexterm" name="d0e8005"></a><a class="indexterm" name="d0e8006"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-extended-ol-syncfreq.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-extended.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-multiplesenders.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">22.6. Synchronisationsfrequenz von E-Mails konfigurieren&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;22.8. Mehrere Absenderadressen</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>